# STM32 Embedded Controller

This repository contains my work from the 2024 Embedded Controller course. I used C on an STM32F411 board to work with GPIO, timers, PWM, sensor inputs and serial communication. The individual exercises led into two team projects: an RC car and an automatic recycling system.

## Projects

The RC-car program reads sensor and command inputs, updates the car's state and drives the motors using PWM. The implementation is in [LAB_RC_Final.c](LAB/LAB_RC_Final.c).

The recycling system uses two controllers. One handles input and sorting actuators; the other measures bin levels with ultrasonic sensors and sends status messages over Bluetooth/UART. The applications are in [final_first_board.c](LAB/final_first_board.c) and [final_second_board.c](LAB/final_second_board.c).

[Watch the recycling system demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

I completed the individual peripheral exercises as coursework. The RC car and recycling system were team projects, and the repository also includes shared course libraries. I do not claim individual authorship of all the code.

## Files

- [PWM and DC motor exercise](LAB/LAB_PWM_DCmotor_21800275_SangheonPark.c)
- [Ultrasonic input-capture exercise](LAB/LAB_Timer_InputCaputre_Ultrasonic_21800275_SangheonPark.c)
- [Course support library](lib)

## Build notes

The archive does not include the complete original board project, startup files and linker configuration. This source snapshot has not been rebuilt or tested on hardware during the portfolio update. A separate local RC-car build does not establish that this archive builds as it stands.

[Original repository](https://github.com/oldprize47/Embbadded_Controller_2024). Original history and attribution are retained.
