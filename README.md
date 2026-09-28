# STM32 Embedded Controller

This repository contains my work from the 2024 Embedded Controller course. I used C on an STM32F411 board to work with GPIO, timers, PWM, sensor inputs and serial communication. The individual exercises led into two team projects: an RC car and an automatic recycling system.

## From peripheral exercises to a working prototype

The earlier labs isolate one part of the microcontroller at a time. GPIO and external interrupts handle switches and simple outputs. Timers provide repeatable timing, PWM changes the motor command, and input capture measures the duration of an ultrasonic sensor's echo pulse. The later projects combine these functions, so a sensor reading affects the program's state and then the actuator output.

This progression is the useful way to read the archive: begin with an individual peripheral exercise, then look at how the same kind of input or output appears in the RC car or recycling system. The support functions in [lib](lib) include course material as well as work used in the assignments.

## Projects

The RC-car program reads sensor and command inputs, updates the car's state and drives the motors using PWM. The implementation is in [LAB_RC_Final.c](LAB/LAB_RC_Final.c).

The car has manual and line-following modes. In manual operation, Bluetooth commands select movement and speed. In automatic operation, two infrared reflectance sensors provide left/right information, and the program changes the motor outputs to follow the line. An ultrasonic sensor provides the obstacle-stop condition. I participated across the implementation with my teammate, using the peripheral work from the earlier labs.

The recycling system uses two controllers. One handles input and sorting actuators; the other measures bin levels with ultrasonic sensors and sends status messages over Bluetooth/UART. The applications are in [final_first_board.c](LAB/final_first_board.c) and [final_second_board.c](LAB/final_second_board.c).

The recycling prototype follows a sequence: recognise the user and item, select the sorting path, open the appropriate doors, detect the deposit, close the mechanism and report completion. My work focused on receiving and interpreting UART information, the sorting sequence, actuator control and bin-level decisions. My teammate handled reading and transmitting barcode IDs, and we integrated the two controllers together.

[Watch the recycling system demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

I completed the individual peripheral exercises as coursework. The RC car and recycling system were team projects, and the repository also includes shared course libraries. I do not claim individual authorship of all the code.

## Files

- [PWM and DC motor exercise](LAB/LAB_PWM_DCmotor_21800275_SangheonPark.c)
- [Ultrasonic input-capture exercise](LAB/LAB_Timer_InputCaputre_Ultrasonic_21800275_SangheonPark.c)
- [Course support library](lib)

## What the saved demonstrations establish

The recycling demonstration shows the course prototype handling its registered items and reporting status. It is a small physical prototype with a constrained item shape and mechanism, not a general waste-recognition system. The source uses barcode information to choose a category; it does not infer material from a camera image.

The individual labs and team demonstrations are historical course results. The build below is a separate check made during the portfolio update. Keeping those two kinds of evidence separate makes it clear what can be reproduced from this repository today.

## Build notes

The RC-car program, selected peripheral labs and supporting files were updated from my local coursework on 28 September 2026. The [PlatformIO configuration](platformio.ini) builds the RC-car target for the Nucleo F411RE with the CMSIS framework:

```sh
pio run -e rc_car
```

This repository configuration built successfully during the update. It excludes the alternative `ecUART2_simple.c` implementation to avoid duplicate UART symbols. Existing compiler warnings remain, including ADC pointer types and printf argument types. This is a compile check for the RC-car target; it does not validate the recycling applications, board wiring, calibration or physical operation. No firmware was flashed.

[Original repository](https://github.com/oldprize47/Embbadded_Controller_2024). Original history and attribution are retained.
