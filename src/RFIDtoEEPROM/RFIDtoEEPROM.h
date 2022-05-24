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

#if !defined(ARDUINO_ARCH_RP2040)

class RFIDtoEEPROM : public Card
{
  public:
    RFIDtoEEPROM(uint8_t byteNumber = 4);
};

#endif

class RFIDtoEEPROM_I2C : public Card
{
  public:
    //EEPROM size in kbits.
    enum eeprom_size_t
    {
      kbits_4 = 4,
      kbits_8 = 8,
      kbits_16 = 16,
      kbits_32 = 32,
      kbits_64 = 64,
      kbits_128 = 128,
      kbits_256 = 256,
      kbits_512 = 512,
      kbits_1024 = 1024,
      kbits_2048 = 2048
    };
    // I2C Clock Frequencies.
    enum twiClockFreq_t
    {
      twiClock100kHz = 100000,
      twiClock400kHz = 400000
    };

    RFIDtoEEPROM_I2C(eeprom_size_t eepromSize = kbits_256, uint8_t address = 0x50, uint8_t byteNumber = 4);

    void begin(twiClockFreq_t twiFreq = twiClock100kHz);
};

#endif  // _RFIDtoEEPROM_h
