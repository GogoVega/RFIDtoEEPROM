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
#include <EEPROM.h>
#include <Wire.h>

/*!
    @brief Read Code from EEPROM.
    @param address Departure address for reading.
    @param Code Variable that will be modified by reading.
    @param byteNumber The Number of byte to read.
*/
void Code::Read(uint8_t address, byte* Code, uint8_t byteNumber)
{
  if (_local) {
    for (uint8_t n = 0; n < byteNumber; n++) {
      Code[n] = EEPROM.read(address + n);
    }
  } else {
    Wire.beginTransmission(_eepromAddr);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(_eepromAddr, byteNumber);

    for (uint8_t i = 0; i < byteNumber; i++) {
      Code[i] = Wire.read();
    }
  }
}


/*!
    @brief Write Code to EEPROM.
    @param address Departure address for writing.
    @param Code Code to write.
    @param byteNumber The Number of byte to write.
*/
void Code::Write(uint8_t address, byte* Code, uint8_t byteNumber)
{
  if (_local) {
    for (uint8_t n = 0; n < byteNumber; n++) {
      EEPROM.update((address + n), Code[n]);
    }
  } else {
    Wire.beginTransmission(_eepromAddr);
    Wire.write(address);
    Wire.write(Code, byteNumber);
    Wire.endTransmission();
    delayMicroseconds(500); 
  }
}


/*!
    @brief Read byte from EEPROM.
    @param address Address for reading.
    @return the byte read (uint8_t).
*/
uint8_t Code::Read(uint8_t address)
{
  uint8_t data;

  Code::Read(address, &data, 1);
  return data;
}


/*!
    @brief Write byte to EEPROM.
    @param address Address for writing.
    @param data the byte to write.
*/
void Code::Write(uint8_t address, uint8_t data)
{
  Write(address, &data, 1);
}


/*!
    @brief Returns the Number of Cells in the EEPROM.
    @return the Number of Cells in the EEPROM (uint16_t).
*/
uint16_t Code::Length()
{
  if (_local)
    return EEPROM.length();

  return _eepromSize;
}
