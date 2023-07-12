# Hitbox Controller

## Parts List

1. Arduino Mega 2560 (Rev. 3)
1. (15x) 30mm EG Starts LED Arcade Button
1. 2' x 2' Plywood
    - Cut down to 1' x 1' for both top and bottom.
    - Cut down the left over to (2x) 1' x 1 1/2" for the two sides.
1. (4x) Nylon Standoff

## Setup Arduino

1. Upload the `hitbox_controller/hitbox_controller.ino` sketch onto Arduino Mega 2560 (Rev. 3) board.
1. On Windows, download and install [FLIP](https://www.microchip.com/en-us/development-tool/flip).
1. Navigate to **Device** > **Select...** and ensure `ATmega16U2` is selected.
1. Navigate to **Settings** > **Communication** > **USB** and click the **Open** button from the next window.
1. Navigate to **File** > **Load HEX File...** and navigate to the local repository's `firmware` directory.
    - Select the `Arduino-keyboard.hex` file to flash the firmware to treat the Arduino as a keyboard.
    - Select the `Arduino-usbserial-atmega16u2-Mega2560-Rev3.hex` file to flash the firmware to reset the Arduino.  
    **Note:** This firmware is required to be running in order to update the sketch.
1. Reboot the Arduino by unplugging and re-plugging in the USB.

## Layout Template

The default layout template uses 24mm buttons for all buttons except for the "Up" key button, which uses a 30mm button. I am using 30mm buttons for all buttons. I've also scaled the layout template by 25% because I have larger hands.

![layout template](images/Layout%20Template.png)

## Lessons Learned

- Even with the layout template scaled by 25% the lock nuts were tightly grouped. In order to alleviate this the layout template should be scaled to something greater than 25%.
