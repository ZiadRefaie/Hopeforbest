# LCD Game Project

An AVR-based game inspired by the Chrome browser's dinosaur game. This project uses an LCD screen to create a simple and engaging experience where the player must avoid obstacles by jumping.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## About

This project recreates the Chrome browser's dinosaur game using an ATMEGA32 and an LCD screen. The player controls a character (a dinosaur) that must jump over obstacles. This project demonstrates how to interface microcontrollers with an LCD and provides a fun, interactive way to learn more about embedded systems.

## Features

- Gameplay inspired by the Chrome dinosaur game
- LCD interface 16x2
- Uses an AVR evaluation kit ( ATMEGA32)
- Real-time obstacle generation and character control
- PushButtons for the controls of the character

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/zidrar/lcd-game.git
    ```
2. Navigate to the project directory:
    ```bash
    cd lcd-game
    ```
3. Ensure you have the following files in your project:
    - `LCD_interface.h`
    - `LCD_prog.c`
    - `LCD_config.h`
    - `DIO_interface.h`
    - `DIO_prog.c`
    - `STD_TYPE.h`
    - `BIT_MATH.h`
4. Connect the AVR evaluation kit and LCD using the provided schematics.

## Usage

1. Power on the circuit.
2. The game starts automatically, similar to the Chrome browser's dinosaur game.
3. Use the designated button or control to make the dinosaur jump over obstacles.
4. The objective is to avoid obstacles for as long as possible.

## Contributing

Contributions aren't welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

Created by [Ziad Refaie](https://github.com/zidrar) - feel free to reach out with any questions or suggestions!
