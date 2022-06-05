# RFID to EEPROM Change Log

## v1.1.0
 - New Features
   - Support for I2C EEPROM.
   - Support for ESP32, ESP8266 and Raspberry Pi Pico.
   - Checks if the Card has already been saved for `SaveCard()`.
   - Checks if Code size matches `ByteNumber` defined in Constructor.
   - Debug option (print error message to Serial Monitor).

 - Changes
   - Using pages in the `EraseAllCards()` function to speed up writing.

## v1.0.0
 Initial commit