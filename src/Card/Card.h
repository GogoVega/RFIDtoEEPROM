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

#ifndef Card_h
#define Card_h

#include <Code.h>

class Card : protected Code
{
  public:
    Card(uint8_t byteNumber = 4);

    template <typename T>
    bool CardCheck(T &t)
    {
      byte *Code = (byte *)&t;
      return CardCheck(Code, sizeof(T));
    }

    template <typename T>
    bool SaveCard(T &t)
    {
      byte *Code = (byte *)&t;
      return SaveCard(Code, sizeof(T));
    }

    void ClearCardNumber(void);
    void EraseAllCards(void);
    uint8_t CardNumber(void);
    uint8_t MaxCards(void);

  private:
    bool CardCheck(byte *Code, uint8_t size);
    bool SaveCard(byte *Code, uint8_t size);
    bool WriteCheck(byte *Code, uint8_t nbr);
    void CardRestoration(uint8_t nbr);

  protected:
    uint8_t _byteNumber;
    uint8_t _maxCards;
};

#endif // _Card_h
