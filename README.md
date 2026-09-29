# STM32 Automatic Recycling System

This project is a recycling-bin prototype that accepts an item through one entrance, selects a bin from registered barcode information, awards user points and reports when a bin is full. It was built for the 2024 Embedded Controller course using two STM32F411RE controllers, sorting doors, a deposit sensor and ultrasonic level sensors.

[Watch the team demonstration](https://www.youtube.com/watch?v=dkphMHEKzxE).

## Project goal

Identify a registered item from its barcode, direct it to the matching bin and report when a bin is full.

![Project goal: stm32-automatic-recycling-system](docs/goals/project-focus-v1.png)

AI-generated concept illustration. Device appearance, interface layout and example graphics are illustrative, not project photographs or measured results.

## Where it could be used

A similar system could support an indoor recycling station in a university or office where accepted items have known barcodes. Barcode lookup would select the sorting category, while ultrasonic fullness reports could help staff decide which bin to empty. The project demonstrates these ideas with registered items; handling arbitrary waste, unreadable barcodes or a wider range of container shapes would require further development.

## At a glance

![Automatic recycling system](docs/flowcharts/recycling.png)

Overview reconstructed from the documented project and code. Results and verification limits are described below. [SVG](docs/flowcharts/recycling.svg)

## System configuration and team

The first controller handles user/item input, two stepper motors, a servo and the deposit sensor. It sends a user index to the second controller over UART. The second controller reads three ultrasonic sensors, updates points and sends status messages over Bluetooth/UART. The boards provide the system's hardware division; the team's work was divided by function rather than by exclusive ownership of a board.

방준혁 developed barcode-based member and recyclable-category recognition and UART transmission. Sangheon Park developed the deposit and sorting sequence, including the stepper motors, servo entrance and infrared deposit detection. He also handled ultrasonic fullness detection, user points, Bluetooth messages and LED status indication. Both members assembled the mechanism, connected the boards and tested the complete prototype.

Both team members contributed to the completed application and integration. The repository also contains course support code. Each board retains its own support-library variant.

## A deposit through the system

A deposit begins with registered member and product barcode input. The selected category determines the sorting path. The mechanism opens the path and entrance, checks the deposit sensor, then closes the mechanism and sends the user index to the second controller. That controller updates points and reports completion. Ultrasonic level monitoring provides the separate full-bin notification.

This separates two flows that run in the same system: the sequence for one deposit and the continuing check of bin capacity. The report's algorithm section and the two board applications describe these flows; physical board boundaries do not represent exclusive ownership by either team member.

The three ultrasonic sensors measure the remaining space above the contents. This is a distance-based indication of fullness, not a measurement of weight or an image-based classification of the material. The prototype uses known barcode information for its sorting category.

The separately tested parts were assembled into a physical mechanism, with sensors and wiring positioned for integrated operation. The course report records successful operation for registered users and products, door movement, deposit detection and full-bin notifications. Its sloped mechanism was designed around items such as rounded plastic containers and cans; other shapes were outside the demonstrated scope.

## Source

The applications are in [board 1](firmware/board-1/app/main.c) and [board 2](firmware/board-2/app/main.c). Each board has its own support-library variant; the two should not be combined into one target.

The code uses GPIO, PWM, timers, input capture and UART. Some control paths use blocking delays, and the one-byte inter-board payload has no framing, checksum or freshness information. These are limitations of the original prototype.

## How to read the firmware

Read the first board's application as the deposit sequence and the second board's application as status and level monitoring. Follow the UART reception, the decision made from that input, and the resulting motor or message output. This is more informative than reading the peripheral helper library in isolation.

The archived report and source contain some differences in pin and UART labels, so they are not a verified wiring recipe. The report also records errors when using three ultrasonic sensors together, but the available evidence does not establish a single experimentally proven cause. The demonstration and the source explain the prototype; rebuilding it requires reconciling the board setup.

## Build notes

The original IDE project, startup file, linker script and complete STM32Cube/CMSIS environment are missing. The repository has not been independently compiled, flashed or retested on hardware. [BUILDING.md](BUILDING.md) records the missing dependencies, and the [technical notes](docs/기술-요약.md) describe the source and wiring.

Personal barcode fixtures have been replaced with synthetic values. The repository remains private while joint-code and course-library redistribution rights are unresolved. See [ATTRIBUTION.md](ATTRIBUTION.md) and [NOTICE.md](NOTICE.md).
