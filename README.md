# STM32 Automatic Recycling System

This was a two-person project for the 2024 Embedded Controller course. We used two STM32F411RE boards to read barcodes, operate sorting doors, detect deposited items and monitor how full the bins were.

The first board handles user and item input, two stepper motors, a servo and the deposit sensor. It sends a user index to the second board over UART. The second board reads three ultrasonic sensors, updates points and sends bin-status messages over Bluetooth/UART.

[Watch the team demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

My work focused on receiving and interpreting UART information, selecting the sorting sequence, controlling the doors and judging bin levels from the ultrasonic measurements. My teammate handled barcode ID reading and transmission. We assembled and integrated the two-controller system together. The application and integration were joint work. Course support code is also included, and this copy does not claim that every file was individually written by me.

## A deposit through the system

A registered user and item are identified before the mechanism chooses a bin. The first controller opens the sorting path and entry mechanism, waits for the deposit sensor, closes the mechanism and sends completion information. The second controller maintains the user-point and bin-status side of the demonstration and reports through the Bluetooth serial connection.

The three ultrasonic sensors measure the remaining space above the contents. This is a distance-based indication of fullness, not a measurement of weight or an image-based classification of the material. The prototype uses known barcode information for its sorting category.

I also helped turn the separately tested parts into a physical assembly, placing the mechanism, sensors and wiring so that we could complete integration together. The course report records successful operation for registered users and products, door movement, deposit detection and full-bin notifications. Its sloped mechanism was designed around items such as rounded plastic containers and cans; other shapes were outside the demonstrated scope.

## Source

The applications are in [board 1](firmware/board-1/app/main.c) and [board 2](firmware/board-2/app/main.c). Each board has its own support-library variant; the two should not be combined into one target.

The code uses GPIO, PWM, timers, input capture and UART. Some control paths use blocking delays, and the one-byte inter-board payload has no framing, checksum or freshness information. These are limitations of the original prototype.

## How to read the firmware

Read the first board's application as the deposit sequence and the second board's application as status and level monitoring. Follow the UART reception, the decision made from that input, and the resulting motor or message output. This is more informative than reading the peripheral helper library in isolation.

The archived report and source contain some differences in pin and UART labels, so they are not a verified wiring recipe. The report also records errors when using three ultrasonic sensors together, but the available evidence does not establish a single experimentally proven cause. The demonstration and the source explain the prototype; rebuilding it requires reconciling the board setup.

## Build notes

The original IDE project, startup file, linker script and complete STM32Cube/CMSIS environment are missing. The repository has not been independently compiled, flashed or retested on hardware. [BUILDING.md](BUILDING.md) records the missing dependencies, and the [technical notes](docs/기술-요약.md) describe the source and wiring.

Personal barcode fixtures have been replaced with synthetic values. The repository remains private while joint-code and course-library redistribution rights are unresolved. See [ATTRIBUTION.md](ATTRIBUTION.md) and [NOTICE.md](NOTICE.md).
