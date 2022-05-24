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

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Returns the address according to the Number of Cards
#define OFFSET(a) ((a * _byteNumber) + 1)

/*!
    @brief Constructor for RFIDtoEEPROM library.
    @param byteNumber the number of bytes contained in the RFID Card.
*/
Card::Card(uint8_t byteNumber)
{
  _byteNumber = byteNumber;
  _maxCards = min(((Code::length() - 1) / byteNumber), 255);
}

/*!
    @brief Returns the Number of Cards already registered.
    @return the Number of Cards already registered (uint8_t).
*/
uint8_t Card::CardNumber()
{
  return Code::read(0);
}

/*!
    @brief Returns the maximum Number of Cards that can be registered. The maximum is set at 255.
    @return the maximum Number of Cards (uint8_t).
*/
uint8_t Card::MaxCards()
{
  return _maxCards;
}

/*!
    @brief Reset the Number of Cards to 0.
*/
void Card::ClearCardNumber()
{
  Code::write(0, 0);
}

/*!
    @brief Erase all Cards.
    @note The EEPROM memory has a specified life of 100,000 write/erase cycles,
     so you may need to be careful about how often you write to it.
*/
void Card::EraseAllCards()
{
  byte Code[_pageSize] = {};

  for (uint32_t n = 0; n < (Code::length() / _pageSize); n++)
  {
    Code::write((n * _pageSize), Code, _pageSize);
  }
}

/*!
    @brief Restoration of the old Card.
    @param nbr Old Card Number before the failure.
*/
void Card::CardRestoration(uint8_t nbr)
{
  /* Uncomment if you want to reset the Card
  byte Code[_byteNumber] = {};
  Code::write(OFFSET(nbr), Code, _byteNumber);
  */

  Code::write(0, nbr);
}

/*!
    @brief Checks if the Code has been correctly written in the EEPROM.
    @param Code The UID of the RFID Code to Check.
    @param nbr The number of Cards.
    @return true on successful writing (bool).
*/
bool Card::WriteCheck(byte *Code, uint8_t nbr)
{
  byte CodeRead[_byteNumber];

  if (Code::read(0) != (nbr + 1))
    return (false);

  Code::read(OFFSET(nbr), CodeRead, _byteNumber);
  for (uint8_t n = 0; n < _byteNumber; n++)
  {
    if (Code[n] != CodeRead[n])
      return (false);
  }

  return (true);
}

/*!
    @brief Save the New Card to EEPROM.
    @param Code The UID of the RFID Code to save.
    @return true on successful saving (bool).
*/
bool Card::SaveCard(uint8_t *Code, uint8_t size)
{
  const uint8_t nbr = CardNumber();

  // if size different from Constructor or better than 16
  if ((size != _byteNumber) || (size > _pageSize))
    return (NULL);

  // if Number of Cards over limit!
  if (nbr >= _maxCards)
    return (false);

  // if Card already saved!
  if (CardCheck(Code, size))
    return (true);

  Code::write(OFFSET(nbr), Code, _byteNumber);

  Code::write(0, (nbr + 1));

  if (!WriteCheck(Code, nbr))
  {
    CardRestoration(nbr);
    return (false);
  }

  return (true);
}

/*!
    @brief Check if the Card Matches with a Card saved in the EEPROM.
    @param Code The UID of the RFID Code to Check.
    @return true if a Card Matches (bool).
*/
bool Card::CardCheck(uint8_t *Code, uint8_t size)
{
  const uint8_t nbr = CardNumber();
  byte CodeRead[_byteNumber];

  // if size different from Constructor or better than 16
  if ((size != _byteNumber) || (size > _pageSize))
    return (NULL);

  for (uint8_t i = 0; i < nbr; i++)
  {
    uint8_t match = 0;

    Code::read(OFFSET(i), CodeRead, _byteNumber);
    for (uint8_t n = 0; n < _byteNumber; n++)
    {
      if (Code[n] == CodeRead[n])
        match++;
    }

    if (match == _byteNumber)
    {
      return (true);
    }
  }

  return (false);
}
