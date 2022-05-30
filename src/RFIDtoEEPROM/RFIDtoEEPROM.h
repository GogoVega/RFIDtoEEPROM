// MIT License

// Copyright (c) 2022 Gauthier Dandele

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef RFIDtoEEPROM_h
#define RFIDtoEEPROM_h

#include <Card.h>
#include <Wire.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 32
#endif

//EEPROM size in Kbits.
enum eeprom_size_t
{
  KBITS_1 = 1,
  KBITS_2 = 2,
  KBITS_4 = 4,
  KBITS_8 = 8,
  KBITS_16 = 16,
  KBITS_32 = 32,
  KBITS_64 = 64,
  KBITS_128 = 128,
  KBITS_256 = 256,
  KBITS_512 = 512,
  KBITS_1024 = 1024,
  KBITS_2048 = 2048
};

// I2C Clock Frequencies.
enum twiClockFreq_t
{
  TWICLOCK100KHZ = 100000,
  TWICLOCK400KHZ = 400000
};

#if !defined(ARDUINO_ARCH_RP2040)

class RFIDtoEEPROM : public Card
{
  public:
    RFIDtoEEPROM(uint8_t byteNumber = 4);

    #if defined(ESP32) || defined(ESP8266)
    void begin(uint32_t eepromSize);
    #endif
};

#endif

class RFIDtoEEPROM_I2C : public Card
{
  public:
    RFIDtoEEPROM_I2C(eeprom_size_t eepromSize = KBITS_256, uint8_t address = 0x50, uint8_t byteNumber = 4);

    void begin(twiClockFreq_t twiFreq = TWICLOCK100KHZ);
};

#endif // _RFIDtoEEPROM_h
