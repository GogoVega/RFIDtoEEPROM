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

#if defined(ARDUINO_ARCH_RP2040)

/*!
    @brief Read Code from EEPROM.
    @param address Departure address for reading.
    @param Code Variable that will be modified by reading.
    @param byteNumber The Number of byte to read.
*/
void Code::Read(uint8_t address, byte* Code, uint8_t byteNumber)
{
  while (isBusy())
    delayMicroseconds(100);

  Wire.beginTransmission((uint8_t) _eepromAddr);
  if (_twoAddress) Wire.write((uint8_t) (address >> 8));
  Wire.write((uint8_t) (address & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom((uint8_t) _eepromAddr, (uint8_t) byteNumber);

  uint8_t i = 0;
  while (Wire.available())
  {
    Code[i++] = Wire.read();
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
  while (isBusy())
    delayMicroseconds(100);

  Wire.beginTransmission((uint8_t) _eepromAddr);
  if (_twoAddress) Wire.write((uint8_t) (address >> 8));
  Wire.write((uint8_t) (address & 0xFF));
  Wire.write(Code, (uint8_t) byteNumber);
  Wire.endTransmission();

  delayMicroseconds(500);
}


/*!
    @brief Returns the Number of Cells in the EEPROM.
    @return the Number of Cells in the EEPROM (uint16_t).
*/
uint16_t Code::Length()
{
  return (_eepromSize * 128);
}

#else

#include <EEPROM.h>

/*!
    @brief Read Code from EEPROM.
    @param address Departure address for reading.
    @param Code Variable that will be modified by reading.
    @param byteNumber The Number of byte to read.
*/
void Code::Read(uint8_t address, byte* Code, uint8_t byteNumber)
{
  if (_local)
  {
    for (uint8_t n = 0; n < byteNumber; n++)
    {
      Code[n] = EEPROM.read(address + n);
    }
  }
  else
  {
    while (isBusy())
      delayMicroseconds(100);

    Wire.beginTransmission((uint8_t) _eepromAddr);
    if (_twoAddress) Wire.write((uint8_t) (address >> 8));
    Wire.write((uint8_t) (address & 0xFF));
    Wire.endTransmission();
    Wire.requestFrom((uint8_t) _eepromAddr, (uint8_t) byteNumber);

    uint8_t i = 0;
    while (Wire.available())
    {
      Code[i++] = Wire.read();
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
  if (_local)
  {
    for (uint8_t n = 0; n < byteNumber; n++)
    {
      #if defined(ESP8266) || defined(ESP32)
      EEPROM.write((address + n), Code[n]);
      #elif defined(__AVR__)
      EEPROM.update((address + n), Code[n]);
      #endif
    }
  }
  else
  {
    while (isBusy())
      delayMicroseconds(100);

    Wire.beginTransmission((uint8_t) _eepromAddr);
    if (_twoAddress) Wire.write((uint8_t) (address >> 8));
    Wire.write((uint8_t) (address & 0xFF));
    Wire.write(Code, (uint8_t) byteNumber);
    Wire.endTransmission();

    delayMicroseconds(500);
  }
}


/*!
    @brief Returns the Number of Cells in the EEPROM.
    @return the Number of Cells in the EEPROM (uint16_t).
*/
uint16_t Code::Length()
{
  if (_local)
    return EEPROM.length();

  return (_eepromSize * 128);
}

#endif

/*!
    @brief Read byte from EEPROM.
    @param address Address for reading.
    @return the byte read (uint8_t).
*/
uint8_t Code::Read(uint8_t address)
{
  uint8_t data;

  Read(address, &data, 1);
  return (data);
}


/*!
    @brief Write byte to EEPROM.
    @param address Address for writing.
    @param data the byte to write.
*/
void Code::Write(uint8_t address, uint8_t data)
{
  if (Read(address) != data)
    Write(address, &data, 1);
}


/*!
    @brief Check if device is not answering (currently writing).
    @return Returns true if writing in progress (bool).
*/
bool Code::isBusy()
{
  Wire.beginTransmission((uint8_t) _eepromAddr);
  if (!Wire.endTransmission())
    return (false);

  return (true);
}
