/*
 * LCD Game.c
 *
 * Created: 19/08/2024 12:16:00 م
 * Author : zidrar
 */ 
#include "BIT_MATH.h"
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>


u8 Character[] = {0b01110,0b01110,0b00100,0b11111,0b10101,0b00100,0b01110,0b11011};
u8 Obstacle_1 [] = {0b00100,0b00101,0b10101,0b10111,0b01100,0b00110,0b00100,0b00100};
	

int main(void)
{	
	u8 fail= 0, i=0,Jumps=0;
	u16 Character_Position=3;
	
	
	DIO_voidSetPinDir(DIO_PORTB,DIO_PIN0,INPUT);
	DIO_voidSetPortDir(DIO_PORTB,0x0E);
	DIO_voidSetPortDir(DIO_PORTA,0xf0);
	DIO_voidSetPinDir(DIO_PORTD,DIO_PIN2,INPUT);
	LCD_voidInit();
	
	LCD_voidGotoxy(1,0);
	LCD_voidSendString("Stickman games");
	LCD_voidGotoxy(0,1);
	LCD_voidSendString("Press any key.");
		while (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2) == 0);
	_delay_ms(30);
		while (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2) == 1);
	LCD_voidSendCommand(1);

	 while (1) 
    {
		LCD_voidGotoxy(8,0);
		LCD_voidSendString("Score:");
		LCD_voidSendNum(Jumps);
		for (i=0;i<16;i++)
		{
				if (DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0) == 1)
				{
					LCD_voidDrawData(0,Character,Character_Position,0);
					LCD_voidGotoxy(Character_Position, 1);
				    LCD_voidSendString(" ");
					Jumps++;
				}
				else if( 16-i == Character_Position && DIO_u8ReadpinVal(DIO_PORTB,DIO_PIN0) == 0 )
				{
					LCD_voidSendCommand(1);
					LCD_voidGotoxy(0,0);
					LCD_voidSendString("You Lost");
					Jumps =0;
					fail++;
					break;
				}
				else
				{
					LCD_voidGotoxy(0, 0);
					LCD_voidSendString("      ");
					LCD_voidDrawData(0,Character,Character_Position,1);
				}
				LCD_voidDrawData(1,Obstacle_1,16-i,1);
				_delay_ms(100);
				  if (16-i > 0) {
					  LCD_voidGotoxy(16-i, 1);
					  LCD_voidSendString(" ");

				  }
		}	
	i=0;		
		if (fail ==1)
			{	
				_delay_ms(500);
				i=16;
				fail=0;
				LCD_voidGotoxy(0,1);
				LCD_voidSendString("Press any key.");
				while (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2) == 0);
				_delay_ms(30);
				while (DIO_u8ReadpinVal(DIO_PORTD,DIO_PIN2) == 1);
				LCD_voidSendCommand(1);
			}

    }
	
}

