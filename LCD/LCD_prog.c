/*
 * LCD_prog.c
 *
 * Created: 8/17/2024 2:06:16 PM
 *  Author: AMIT
 */ 

#include "BIT_MATH.h" 
#include "STD_TYPE.h" 
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"

#define  F_CPU 16000000UL 
#include <util/delay.h>


void LCD_voidSHD(u8  copy_u8data) {
	
	u8 LCD_PINS[4]={LCD_D4_PIN,LCD_D5_PIN,LCD_D6_PIN,LCD_D7_PIN} ; 
	u8 LOC_u8in=0 ; 	
		for(LOC_u8in=0;LOC_u8in<4;LOC_u8in++)
	    {
			DIO_voidSetPinVal(LCD_DPORT,LCD_PINS[LOC_u8in],GET_BIT(copy_u8data,LOC_u8in)) ; 
		}
	
}

void LCD_voidSendEnable(){
	 /*Send enable pulse*/
	 DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,HIGH) ;
	 _delay_ms(2) ;
	 DIO_voidSetPinVal(LCD_CPORT,LCD_EN_PIN,LOW) ;
}

void LCD_voidSendData(u8 copy_u8data){
		/*make rs as low to send command  */
		DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,HIGH) ;
		/*make rw as low to write command   */
		DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;
	#if LCD_MODE == _4_BIT_MODE
	LCD_voidSHD(copy_u8data>>4) ;  // 1100 1100
	LCD_voidSendEnable() ;
	LCD_voidSHD(copy_u8data) ;
	LCD_voidSendEnable() ;
	
	#elif LCD_MODE ==_8_BIT_MODE
	/* send command */
	DIO_voidSetPortVal(LCD_DPORT,copy_u8data) ;  //  0B11100111
	LCD_voidSendEnable() ;
	
	#endif
}
void LCD_voidSendCommand(u8 copy_u8command){
	
	/*make Rs as low to send command  */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RS_PIN,LOW) ; 
	/*make Rw as low to write command   */
	DIO_voidSetPinVal(LCD_CPORT,LCD_RW_PIN,LOW) ;
	
	#if LCD_MODE == _4_BIT_MODE 
	  LCD_voidSHD(copy_u8command>>4) ;  // 1100 1100 
	   LCD_voidSendEnable() ; 
	  LCD_voidSHD(copy_u8command) ; 
	   LCD_voidSendEnable() ;
	#elif LCD_MODE ==_8_BIT_MODE    
	/* send command */
	 DIO_voidSetPortVal(LCD_DPORT,copy_u8command) ;  //  0B11100111
	 LCD_voidSendEnable() ; 
   #endif 
	 

	 
	
}
void LCD_voidInit(void){
	 _delay_ms(40) ; 
	 
	 #if LCD_MODE== _8_BIT_MODE
	 /*send command function set */
	 LCD_voidSendCommand(0b00111000) ; 
	 #elif LCD_MODE ==_4_BIT_MODE 
	     
		  LCD_voidSHD(0b0010) ; 
		  LCD_voidSendEnable() ; 
		  LCD_voidSHD(0b0010) ;
		  LCD_voidSendEnable() ;
		  LCD_voidSHD(0b1000) ; 
		  LCD_voidSendEnable() ;
	#endif 	  
	 /*send command  display on/off */
	 LCD_voidSendCommand(0b00001100) ; 
	 /*send command   LCD CLR */
	 LCD_voidSendCommand(1) ;
	
}


void LCD_voidSendString(u8*str){
	u8 i=0 ; 
	while(str[i] !='\0'){
		
		LCD_voidSendData(str[i]) ; 
		i++ ; 
	}
}
void LCD_voidGotoxy(u8 coopy_u8x ,u8 coopy_u8y ){
	// SET ADDRESS
	u8 DDRAM_Address = coopy_u8x + coopy_u8y*(0x40);
	// SET DDRAM
	SET_BIT(DDRAM_Address,7);
	LCD_voidSendCommand(DDRAM_Address);	
}

void LCD_voidDrawData(u8 pattern , u8* data , u8 x , u8 y){
	
	u8 Loc_i =0;
	u8 address_CGRAM = pattern*8 ;
	CLR_BIT(address_CGRAM,7);
	SET_BIT(address_CGRAM,6);
	LCD_voidSendCommand(address_CGRAM);
	for (Loc_i=0 ;Loc_i<8 ; Loc_i++)
	{
		LCD_voidSendData(data[Loc_i]);
	}
	LCD_voidGotoxy(x,y);
	LCD_voidSendData(pattern);
}

void LCD_voidSendNum (u8 copy_u8data){
 u8 buffer[10];
 u8 i = 0;
	 if (copy_u8data == 0) {
		 LCD_voidSendData('0');
	 }
	 while (copy_u8data  > 0) {
		 buffer[i] = (copy_u8data % 10) + '0';
		 copy_u8data  /= 10;
		 i++;
	 }
	 while (i > 0) {
		 i--;
		 LCD_voidSendData(buffer[i]);
	 }
	};
	
	
	

