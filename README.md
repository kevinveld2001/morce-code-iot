## Morse code blinker object
This object is connected to toto and will bink all letters sent using mqtt.

The code is written for the nano_33_iot. You can change this in the `platformio.ini`.
The led's that blink are hardcoded in `setup` and `setLeds` functions.

To connect the object with wifi and with toto you need to copy the `secrets.h.example` to `secrets.h` and fill it in with the wifi name, password and toto credentials.

After that, you can send letters to the blinker using mqtt.
