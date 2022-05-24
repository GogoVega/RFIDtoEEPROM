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

#ifndef BUFFER_LENGTH
#define BUFFER_LENGTH 32
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#if defined(ARDUINO_ARCH_RP2040)

/*!
    @brief Read Code from EEPROM.
    @param address Departure address for reading.
    @param Code Variable that will be modified by reading.
    @param byteNumber The Number of byte to read.
*/
void Code::read(uint32_t address, byte *Code, uint8_t byteNumber)
{
  uint8_t rxStatus = 0;

  while (byteNumber > 0)
  {
    uint8_t bytePage = _pageSize - ( address & (_pageSize - 1) );
    uint8_t byteRead = min((min(bytePage, byteNumber)), (BUFFER_LENGTH - 2));

    while (isBusy())
      delayMicroseconds(100);

    Wire.beginTransmission((uint8_t)_eepromAddr);
    if (_twoAddress) Wire.write((uint8_t)(address >> 8)); // MSB
    Wire.write((uint8_t)(address & 0xFF));  // LSB
    rxStatus = Wire.endTransmission();
    if (rxStatus != 0) break; // Read error

    Wire.requestFrom((uint8_t)_eepromAddr, (uint8_t)byteRead);

    uint8_t i = 0;
    while (Wire.available())
    {
      Code[i++] = Wire.read();
    }

    address += byteRead;     // Increment the EEPROM address
    Code += byteRead;        // Increment the input data pointer
    byteNumber -= byteRead;  // Decrement the number of bytes left to read
  }
}

/*!
    @brief Write Code to EEPROM.
    @param address Departure address for writing.
    @param Code Code to write.
    @param byteNumber The Number of byte to write.
*/
void Code::write(uint32_t address, byte *Code, uint8_t byteNumber)
{
  uint8_t txStatus = 0;

  while (byteNumber > 0)
  {
    uint8_t bytePage = _pageSize - ( address & (_pageSize - 1) );
    uint8_t byteWrite = min((min(bytePage, byteNumber)), (BUFFER_LENGTH - 2));

    while (isBusy())
      delayMicroseconds(100);

    Wire.beginTransmission((uint8_t)_eepromAddr);
    if (_twoAddress) Wire.write((uint8_t)(address >> 8)); // MSB
    Wire.write((uint8_t)(address & 0xFF));  // LSB
    Wire.write(Code, (uint8_t)byteWrite);
    txStatus = Wire.endTransmission();
    if (txStatus != 0) break; // Write error

    address += byteWrite;     // Increment the EEPROM address
    Code += byteWrite;        // Increment the input data pointer
    byteNumber -= byteWrite;  // Decrement the number of bytes left to write

    delayMicroseconds(500);
  }
}

/*!
    @brief Returns the Number of Cells in the EEPROM.
    @return the Number of Cells in the EEPROM (uint32_t).
*/
uint32_t Code::length()
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
void Code::read(uint32_t address, byte *Code, uint8_t byteNumber)
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
    uint8_t rxStatus = 0;

    while (byteNumber > 0)
    {
      uint8_t bytePage = _pageSize - ( address & (_pageSize - 1) );
      uint8_t byteRead = min((min(bytePage, byteNumber)), (BUFFER_LENGTH - 2));

      while (isBusy())
        delayMicroseconds(100);

      Wire.beginTransmission((uint8_t)_eepromAddr);
      if (_twoAddress) Wire.write((uint8_t)(address >> 8)); // MSB
      Wire.write((uint8_t)(address & 0xFF));  // LSB
      rxStatus = Wire.endTransmission();
      if (rxStatus != 0) break; // Read error

      Wire.requestFrom((uint8_t)_eepromAddr, (uint8_t)byteRead);

      uint8_t i = 0;
      while (Wire.available())
      {
        Code[i++] = Wire.read();
      }

      address += byteRead;     // Increment the EEPROM address
      Code += byteRead;        // Increment the input data pointer
      byteNumber -= byteRead;  // Decrement the number of bytes left to read
    }
  }
}

/*!
    @brief Write Code to EEPROM.
    @param address Departure address for writing.
    @param Code Code to write.
    @param byteNumber The Number of byte to write.
*/
void Code::write(uint32_t address, byte *Code, uint8_t byteNumber)
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
    uint8_t txStatus = 0;

    while (byteNumber > 0)
    {
      uint8_t bytePage = _pageSize - ( address & (_pageSize - 1) );
      uint8_t byteWrite = min((min(bytePage, byteNumber)), (BUFFER_LENGTH - 2));

      while (isBusy())
        delayMicroseconds(100);

      Wire.beginTransmission((uint8_t)_eepromAddr);
      if (_twoAddress) Wire.write((uint8_t)(address >> 8)); // MSB
      Wire.write((uint8_t)(address & 0xFF));  // LSB
      Wire.write(Code, (uint8_t)byteWrite);
      txStatus = Wire.endTransmission();
      if (txStatus != 0) break; // Write error

      address += byteWrite;     // Increment the EEPROM address
      Code += byteWrite;        // Increment the input data pointer
      byteNumber -= byteWrite;  // Decrement the number of bytes left to write

      delayMicroseconds(500);
    }
  }
}

/*!
    @brief Returns the Number of Cells in the EEPROM.
    @return the Number of Cells in the EEPROM (uint32_t).
*/
uint32_t Code::length()
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
uint8_t Code::read(uint32_t address)
{
  uint8_t data;

  read(address, &data, 1);
  return (data);
}

/*!
    @brief Write byte to EEPROM.
    @param address Address for writing.
    @param data the byte to write.
*/
void Code::write(uint32_t address, uint8_t data)
{
  if (read(address) != data)
    write(address, &data, 1);
}

/*!
    @brief Check if device is not answering (currently writing).
    @return true if writing in progress (bool).
*/
bool Code::isBusy()
{
  Wire.beginTransmission((uint8_t)_eepromAddr);
  if (!Wire.endTransmission())
    return (false);

  return (true);
}

/*!
    @brief Returns the page size of EEPROM.
    @param eepromSize EEPROM size in Kbits.
    @return the page size of EEPROM (uint8_t).
*/
uint8_t Code::pageSize(uint32_t eepromSize)
{
  if (eepromSize < RFIDtoEEPROM_I2C::kbits_4)
    return 8;
  else if (eepromSize < RFIDtoEEPROM_I2C::kbits_32)
    return 16;
  else if (eepromSize < RFIDtoEEPROM_I2C::kbits_128)
    return 32;
  else if (eepromSize < RFIDtoEEPROM_I2C::kbits_512)
    return 64;

  return 128;
}
