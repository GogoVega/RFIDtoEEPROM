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

#include <RFIDtoEEPROM.h>
#include <Wire.h>

/*!
    @brief Constructor for RFIDtoEEPROM_I2C library.
    @param eepromSize EEPROM size in kbits.
    @param address I2C address of EEPROM.
    @param byteNumber the number of bytes contained in the RFID Card.
*/
RFIDtoEEPROM_I2C::RFIDtoEEPROM_I2C(eeprom_size_t eepromSize, uint8_t address, uint8_t byteNumber) : Card(byteNumber)
{
  _local = false;
  _eepromAddr = address;
  _eepromSize = eepromSize;
  _twoAddress = eepromSize > kbits_16 ? true : false;
}


/*!
    @brief Set the I2C communication frequency.
    @param twiFreq Frequency.
*/
void RFIDtoEEPROM_I2C::begin(twiClockFreq_t twiFreq)
{
  Wire.begin();
  Wire.setClock(twiFreq);
  Wire.beginTransmission(_eepromAddr);
  if (_twoAddress) Wire.write(0);
  Wire.write(0);
  Wire.endTransmission();
}
