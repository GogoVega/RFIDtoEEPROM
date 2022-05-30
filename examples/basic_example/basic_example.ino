/*
* This library is used to save an RFID Code in the EEPROM and Check if the Code
* corresponds to a Code already saved.
*
* It can be very useful if you use an RFID reader to lock / unlock your Arduino.
*
* This is a basic example that will allow you to:
* - Know the Number of registered Cards
* - Save a New Card to EEPROM
* - Check if the Code provided corresponds to a Code already saved
* - Reset the Number of Cards to 0
* - Erase all Cards.
*
* Warning: you must use the same number of bytes in your functions as defined
* in the Constructor!
*
* Create April 2022
*
* Copyright (c) 2022 Gauthier Dandele
*
* MIT License
*/

#include <RFIDtoEEPROM.h>

#define NUMBYTES 4

// By default, the Number of Bytes in the UID = 4
RFIDtoEEPROM myCard(NUMBYTES);

// Uncomment to use I2C EEPROM (EEPROMSize, I2CAddress, ByteNumber)
// RFIDtoEEPROM_I2C myCard(KBITS_256, 0x50, NUMBYTES);

void setup() {
  Serial.begin(9600);

  // If you don't want to enable debugging, you can remove it
  myCard.beginDebug(Serial);

  // Uncomment to use the emulated EEPROM of the ESP32 or ESP8266
  // Set the desired size in bytes!
  // myCard.begin(8);

  // Uncomment to use I2C EEPROM
  // Wire.begin();
  // myCard.begin();

  // Erase all Cards
  // myCard.EraseAllCards();

  // Reset the Number of Cards
  myCard.ClearCardNumber();

  // Print the Number of Saved Cards
  Serial.print("Number of Saved Cards: ");
  Serial.println(myCard.CardNumber());

  // Print the Number of Recordable Cards
  Serial.print("Number of Recordable Cards: ");
  Serial.println(myCard.MaxCards());

  // Register a new Card
  byte Code[4] = {217, 90, 119, 158};
  Serial.print("UID Cards is: ");
  for (int i = 0; i < NUMBYTES; i++) {
    Serial.print(Code[i], HEX);
  }

  Serial.println();

  Serial.println("Card registration...");

  if (myCard.SaveCard(Code)) {
    Serial.println("Card saved successfully");
  } else {
    Serial.println("Failure during writing!");
  }

  // Print the Number of Saved Cards
  Serial.print("Number of Saved Cards: ");
  Serial.println(myCard.CardNumber());

  Serial.println("Checking Card Matches...");

  // Checks if the Card Matches
  if (myCard.CardCheck(Code)) {
    Serial.println("The Card Matches");
  } else {
    Serial.println("The Card Not Matches!");
  }
}

void loop() {}
