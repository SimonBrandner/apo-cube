# Virtual Peripherals File Descriptions

This project uses a set of files to simulate memory of a virtual peripherals to allow run our program without the `MZ_APO`. Below is a description of each file and its purpose:

## Files and Their Contents

1. `memory/knob_presses.in`
    - **Purpose**: Stores the current state of the RGB knob presses.
    - **Content**: A single byte where each bit represents the state of the knob:
        - Bit 0: Red knob press (1 = pressed, 0 = not pressed)
        - Bit 1: Green knob press
        - Bit 2: Blue knob press
    - **Example**: If both the red and green knobs are pressed, it would be `0b00000011`, depending on the endianness of the system.

2. `memory/knobs.in`
    - **Purpose**: Stores the current RGB values of the knobs.
    - **Content**: A 3 byte values representing the red, green, and blue knob positions (8 bits each).

3. `memory/leds.out`
    - **Purpose**: Represents the state of 32 virtual LEDs.
    - **Content**: A 4 byte * 8 bits binary file where each bit corresponds to the on/off state of an LED (1 = on, 0 = off).
    - **Example**: If first, third, and fifth LEDs are on, the byte would be `0b00010101`, (endianness may also vary).

4. `memory/screen.out`
    - **Purpose**: Represents the state of a virtual screen.
    - **Content**: `SCREEN_WIDTH * SCREEN_HEIGHT` of  `RGB565` values, where each value represents the color of a pixel on the screen.

## Usage and Initialization of Virtual Peripherals

To initialize the virtual peripherals, you can either create the files manually or you can download sample files from the: [Apo Cube Memory Sample](https://github.com/ProfiPoint/apo-cube-utils)

Be sure to include all files in `src/periphs_virtual/memory/` otherwise it won't work.

To run the virtual peripherals UI, you can use the `virtual_peripherals.py` script. This script will read the input files and simulate the behavior of the peripherals. You can also modify the input files to change the state of the peripherals.

To use the virtual peripherals in this program, you can run `make runv`.
