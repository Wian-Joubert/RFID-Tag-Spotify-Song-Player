=====
By Wian Joubert

It's jank, but it's my jank
=====

A SBC project
-----
Components:
Arduino Uno
i2c Monochrome 1.3" 128x64 OLED 4-pin display (works with UF8G2 Library)
RDM6300 125Khz RFID tag/card reader
125Khz RFID tag/cards

Libraries Arduino:
SoftwareSerial.h
U8g2lib.h (Adafruit did not work with my display and I was forced to use this)

Libraries Python:
serial
webbrowser
time
spotipy

Steps:
-----
Run the Arduino code and check the serial monitor for the RFID tag outputs
Change the Tag ID to match your tags in the Python code
Change the songs to what you'd like or add more
Change the Port address and baud to match your system and Arduino
Fill in your client ID and secret according to your Spotify Dev Info
Run it!