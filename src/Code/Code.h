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

#ifndef Code_h
#define Code_h

#include <Arduino.h>
#include <StreamDebug.h>

class Code : public StreamDebug
{
  protected:
    void read(uint32_t address, byte *Code, uint8_t byteNumber);
    uint8_t read(uint32_t address);
    void write(uint32_t address, byte *Code, uint8_t byteNumber);
    void write(uint32_t address, uint8_t data);
    uint8_t pageSize(uint32_t eepromSize);
    uint32_t length(void);

    bool _local;
    bool _twoAddress;
    uint8_t _eepromAddr;
    uint8_t _pageSize = 8;
    uint32_t _eepromSize;

  private:
    bool isBusy(void);
};

#endif // _Code_h
