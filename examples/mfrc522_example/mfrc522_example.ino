/*
* This library is used to save an RFID Code in the EEPROM and Check if the Code
* corresponds to a Code already saved.
*
* It can be very useful if you use an RFID reader to lock / unlock your Arduino.
*
* This is an example with MFRC522 library to retrieve the Code from your Card.
*
* A button will be used to request a Card recording.
*
* Typical pin layout used:
* -----------------------------------------------------------------------------------------
*             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
*             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
* Signal      Pin          Pin           Pin       Pin        Pin              Pin
* -----------------------------------------------------------------------------------------
* RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
* SPI SS      SDA(SS)      10            53        D10        10               10
* SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
* SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
* SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*
* More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
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

#include <MFRC522.h>
#include <RFIDtoEEPROM.h>

#define SS_PIN 6
#define RST_PIN 7
#define BUTTONPIN 8
#define NUMBYTES 4

MFRC522 rfid(SS_PIN, RST_PIN);

// By default, the Number of Bytes in the UID = 4
RFIDtoEEPROM myCard(NUMBYTES);

// Uncomment to use I2C EEPROM (EEPROMSize, I2CAddress, ByteNumber)
// RFIDtoEEPROM_I2C myCard(RFIDtoEEPROM_I2C::kbits_256, 0x50, NUMBYTES);

byte Code[NUMBYTES];

void setup() {
  Serial.begin(9600);

  // If you don't want to enable debugging, you can remove it
  myCard.beginDebug(Serial);

  SPI.begin();
  rfid.PCD_Init();

  // Uncomment to use the emulated EEPROM of the ESP32 or ESP8266
  // Set the desired size in bytes!
  // myCard.begin(16);

  // Uncomment to use I2C EEPROM
  // Wire.begin();
  // myCard.begin();

  // Reset the Number of Cards
  // myCard.ClearCardNumber();

  // Erase all Cards
  // myCard.EraseAllCards();
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      for (int i = 0; i < NUMBYTES; i++) {
        Code[i] = rfid.uid.uidByte[i];
      }

      Serial.println("Card Detected");

      Serial.print("Number of Saved Cards: ");
      Serial.println(myCard.CardNumber());

      Serial.print("UID Cards is: ");
      for (int i = 0; i < NUMBYTES; i++) {
        Serial.print(Code[i], HEX);
      }

      Serial.println();

      if (digitalRead(BUTTONPIN)) {
        Serial.println("Registration Request");
        Serial.println("Registration...");

        if (myCard.SaveCard(Code)) {
          Serial.println("New Card Saved");
          Serial.print("Number of Saved Cards: ");
          Serial.println(myCard.CardNumber());
        } else {
          Serial.println("Failure during writing!");
          Serial.println("Start Again...");
        }
      } else {
        if (!myCard.CardNumber()) {
          Serial.println("No Card added!");
        } else {
          Serial.println("Checking Card Matches...");

          if (myCard.CardCheck(Code)) {
            Serial.println("Card Matches");
          } else {
            Serial.println("Card Not Matches!");
          }
        }
      }

      Serial.println();

      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
    }
  }

  delay(50);
}
