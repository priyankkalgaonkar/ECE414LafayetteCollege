# ECE414_Examples_LafayetteCollege

This repository contains example code and libraries for ECE 414: Embedded Systems at Lafayette College.

## Lab Reference Guide

Use the table below to find the correct example folders for each lab assignment.

| Lab | Topic | Relevant Repository Folders | What to Look For |
| :--- | :--- | :--- | :--- |
| **Lab 1** | Setup & Blinking | `blink2/` | `blink2.c`, `CMakeLists.txt`, `pico_sdk_import.cmake` |
| **Lab 2** | GPIO & Modular C | `gpio_demo/` | `gpio_demo.c` (using `gpio_init_mask()`), `CMakeLists.txt` |
| **Lab 3** | PONG1D & UART | `uart_demo/`, `debounce_sw1/`, `timer/`, `LED3_FSM/` | `uart_demo.c`, `debounce_sw1.c`, `timer.c`, `LED3_FSM.c` |
| **Lab 4** | LCD & Touchscreen | `tft_master/`, `tft_demo/`, `touchscreen_demo/` | `TFTMaster.c/h`, `glcdfont.c`, `TouchScreen.c/h`, `SPIPIO.pio` |
| **Lab 5** | Calculator (Capstone) | `tft_master/`, `touchscreen_demo/`, `timer/`, `LED3_FSM/` | Everything from Lab 4 + `timer.c`, `LED3_FSM.c` (FSM template) |

## Folder Breakdown

| Folder | Description |
| :--- | :--- |
| `blink2/` | Simple LED blinking example (Lab 1) |
| `gpio_demo/` | 8-bit pattern output on GPIO 2–9 (Lab 2) |
| `uart_demo/` | UART echo example for Tera Term testing (Lab 3) |
| `debounce_sw1/` | Software debouncing state machine (Lab 3) |
| `timer/` | Non-blocking timer module using `time_us_32()` (Labs 3 & 5) |
| `LED3_FSM/` | Synchronous Finite State Machine template (Labs 3 & 5) |
| `tft_master/` | Core SPI driver for the Adafruit 2.4" TFT display (Labs 4 & 5) |
| `tft_demo/` | Demo code to verify the TFT display works (Lab 4) |
| `touchscreen_demo/` | Demo code to verify touch detection works (Labs 4 & 5) |

## Important Note

You are welcome to download and use these files as a starting point for your lab assignments, but **follow the course policy of crediting the source of code you are using**. 

- Always copy the example files into your own `LabX` folder in your Git repository. 
- Do **not** modify the files directly in the `ECE414_Examples_LafayetteCollege` repository.

Several of these examples are based on code in the Raspberry Pi Pico examples repository.
