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

#ifndef RFIDtoEEPROM_H
#define RFIDtoEEPROM_H

#include <Arduino.h>

class RFIDtoEEPROM
{
  public:
    RFIDtoEEPROM(uint8_t byteNumber = 4);

    bool CardCheck(byte Code[]);
    bool SaveCard(byte Code[]);
    void ClearCardNumber(void);
    void EraseAllCards(void);
    uint8_t CardNumber(void);
    uint8_t MaxCards(void);

  private:
    bool WriteCheck(byte Code[], uint8_t nbr);
    void CardRestoration(int nbr);
    uint8_t _byteNumber;
    uint8_t _maxCards;
};

#endif  // _RFIDtoEEPROM_H
