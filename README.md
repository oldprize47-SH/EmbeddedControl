# STM32 Automatic Recycling System

This was a two-person project for the 2024 Embedded Controller course. We used two STM32F411RE boards to read barcodes, operate sorting doors, detect deposited items and monitor how full the bins were.

The first board handles user and item input, two stepper motors, a servo and the deposit sensor. It sends a user index to the second board over UART. The second board reads three ultrasonic sensors, updates points and sends bin-status messages over Bluetooth/UART.

[Watch the team demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

The application and integration were joint work. Course support code is also included, and this copy does not claim that every file was individually written by me.

## Source

The applications are in [board 1](firmware/board-1/app/main.c) and [board 2](firmware/board-2/app/main.c). Each board has its own support-library variant; the two should not be combined into one target.

The code uses GPIO, PWM, timers, input capture and UART. Some control paths use blocking delays, and the one-byte inter-board payload has no framing, checksum or freshness information. These are limitations of the original prototype.

## Build notes

The original IDE project, startup file, linker script and complete STM32Cube/CMSIS environment are missing. The repository has not been independently compiled, flashed or retested on hardware. [BUILDING.md](BUILDING.md) records the missing dependencies, and the [technical notes](docs/기술-요약.md) describe the source and wiring.

Personal barcode fixtures have been replaced with synthetic values. The repository remains private while joint-code and course-library redistribution rights are unresolved. See [ATTRIBUTION.md](ATTRIBUTION.md) and [NOTICE.md](NOTICE.md).
