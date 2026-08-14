# STM32 Automatic Recycling System

A two-MCU embedded system that identifies a user and recyclable item by barcode, routes the item with motors, and reports bin fill state from ultrasonic sensors.

## Scope

- **Period:** 2024-2
- **Type:** two-person Embedded Controller course project
- **Target:** STM32F411RE-based controller boards
- **My documented role:** UART barcode receive/parse, user/item classification logic, ultrasonic fill-state processing, and full-bin notification
- **Joint work:** two-board communication and system integration

This portfolio copy contains only the final application-level firmware. Course support drivers, vendor manuals, and unrelated lab assignments are not republished.

## System architecture

```text
User barcode + item barcode
  -> sorter controller (UART receive / lookup / state logic)
  -> stepper gates + servo door + IR completion sensing
  -> inter-MCU UART
  -> fill monitor (3 ultrasonic channels)
  -> point update + Bluetooth full-bin message
```

## Firmware

- `firmware/sorter_controller.c`
  - receives barcode bytes through USART6
  - distinguishes registered users and item categories
  - drives two stepper gates and one RC servo
  - uses an IR sensor to detect disposal completion
  - sends the user index to the second controller through USART1
- `firmware/fill_monitor.c`
  - measures three bin distances with timer input capture
  - updates a per-user point counter
  - reports full-bin state through Bluetooth/UART

## Privacy sanitization

The original course prototype used hardcoded demonstration identifiers. This portfolio copy replaces all user barcodes and user names with synthetic values. Product EAN examples remain only as item-classification fixtures.

## Build and verification boundary

The application files depend on course-specific STM32F4 support headers and drivers that are intentionally not redistributed. Therefore this repository is **not a standalone firmware build**. The migration verification checks source structure, privacy removal, and static consistency; it does not claim a fresh hardware build or bench rerun.

## Limitations

- Barcode mappings are fixed in firmware rather than stored in an external database.
- The project uses blocking delays in parts of the monitoring flow.
- No new hardware-in-the-loop test was performed during portfolio migration.
- Hardware photos/video will be added only after teammate-media and personal-information review.

## Attribution

The final system was built by Sangheon Park and Junhyeok Bang as a two-person course project. This repository does not claim sole authorship and does not grant a new license for course or joint work.
