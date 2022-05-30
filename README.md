# RFID to EEPROM

<p align="left">
  <a href="https://github.com/GogoVega/RFIDtoEEPROM/releases/latest">
    <img src="https://img.shields.io/github/v/release/GogoVega/RFIDtoEEPROM.svg?include_prereleases" alt="GitHub Release Version" />
  </a>
  <a href="https://registry.platformio.org/libraries/gogovega/RFID to EEPROM">
    <img src="https://badges.registry.platformio.org/packages/gogovega/library/RFID to EEPROM.svg" alt="PlatformIO Registry" />
  </a>
  <a href="https://discord.gg/rYgzexA9u4">
    <img src="https://img.shields.io/discord/928317454516641802?color=8ed6fb&label=Discord&logo=discord" alt="ArduiChar Discord" />
  </a>
</p>

Library to write an RFID Code in the [EEPROM](https://docs.arduino.cc/learn/built-in-libraries/eeprom) in order to check if the Code corresponds to a Code already saved.

## Usage

This library is used for saving an RFID Code to your Arduino's EEPROM or I2C EEPROM rather than your Code to avoid **showing your RFID Code**. To then check if the Code corresponds to a Code already registered.

**Warning:** you must use the same number of bytes in your functions as defined in the Constructor!

## How To Use

Go to the Libraries Manager on [PlatformIO](https://platformio.org/platformio-ide) and search for `RFID to EEPROM`. Then you just have to install it in your project.

![PlatformIO](https://raw.githubusercontent.com/GogoVega/RFIDtoEEPROM/master/docs/platformio.png)

Or use `platformIO Core CLI` and paste the following command:

```bash
pio pkg install --library "gogovega/RFID to EEPROM@^1.1.0"
```

## How It Works

### Constructor

- Internal EEPROM

```cpp
RFIDtoEEPROM(uint8_t byteNumber);
```

#### Set emulated EEPROM size (only needed for ESP32 and ESP8266)

```cpp
void begin(uint32_t eepromSize);
```

- I2C EEPROM

```cpp
RFIDtoEEPROM_I2C(eeprom_size_t eepromSize, uint8_t address, uint8_t byteNumber);
```

#### Set I2C BUS Speed

```cpp
void begin(twiClockFreq_t twiFreq);
```

#### Enumerations

Use one of the enumerations below to set EEPROM Size:
```cpp
{
  KBITS_1,
  KBITS_2,
  KBITS_4,
  KBITS_8,
  KBITS_16,
  KBITS_32,
  KBITS_64,
  KBITS_128,
  KBITS_256,
  KBITS_512,
  KBITS_1024,
  KBITS_2048
}
```

And use one of the enumerations below to set twiClock (Wire) Frequence:
```cpp
{
  TWICLOCK100KHZ,
  TWICLOCK400KHZ
}
```

### Enable Debugging

Debugging makes it easier to find errors in a program. To use it, add the following function below your Serial begin and then open your [Serial Monitor](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor) in order to receive error messages if there are any.

```cpp
void beginDebug(Stream &debugPort);
```

### Functions

This library contains several functions:

| Name | Description |
|---|---|
| `CardNumber()` | Returns the number of Cards already registered. |
| `SaveCard()` | Stores the RFID Code of a Card in the EEPROM. Returns `true` if the write succeeds. Otherwise returns `false` and restores the old Card. |
| `CardCheck()` | Checks if the Code received corresponds to a Code already stored in the EEPROM. Returns `true` if a Card matches. |
| `ClearCardNumber()` | Resets the number of recorded Cards to 0. |
| `EraseAllCards()` | Resets all Cards to 0. |
| `MaxCards()` | Returns the maximum number of recordable Cards. Currently **set to 255**. |

**Note:** The EEPROM memory has a specified life of 100,000 write/erase cycles (depends on models), so you may need to be careful about how often you write to it.

## Tested On

- Atmel AT24C256
- Microchip 24C65/P

## Future Features

- Increase the number of recordable Cards (currently set to 255).

## Limitations

- The Number of recordable Cards is fixed at 255.

## License

MIT
