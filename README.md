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

The RC-car program, selected peripheral labs and supporting files were updated from my local coursework on 28 September 2026. The [PlatformIO configuration](platformio.ini) builds the RC-car target for the Nucleo F411RE with the CMSIS framework:

```sh
pio run -e rc_car
```

This repository configuration built successfully during the update. It excludes the alternative `ecUART2_simple.c` implementation to avoid duplicate UART symbols. Existing compiler warnings remain, including ADC pointer types and printf argument types. This is a compile check for the RC-car target; it does not validate the recycling applications, board wiring, calibration or physical operation. No firmware was flashed.

[Original repository](https://github.com/oldprize47/Embbadded_Controller_2024). Original history and attribution are retained.
