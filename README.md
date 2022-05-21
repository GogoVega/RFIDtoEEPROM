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

**Warning:** you must use the same number of bytes in your functions as defined in the Constructor and less than or equal to 16!

## How To Use

Go to the Libraries Manager on [PlatformIO](https://platformio.org/platformio-ide) and search for `RFID to EEPROM`. Then you just have to install it in your project.

![PlatformIO](https://raw.githubusercontent.com/GogoVega/RFIDtoEEPROM/master/docs/platformio.png)

Or use `platformIO Core CLI` and paste the following command:

```bash
pio lib install "gogovega/RFID to EEPROM@^1.1.0"
```

## How It Works

### Constructor

- Internal EEPROM

```cpp
RFIDtoEEPROM(uint8_t byteNumber);
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
```
{
  RFIDtoEEPROM_I2C::kbits_2,
  RFIDtoEEPROM_I2C::kbits_4,
  RFIDtoEEPROM_I2C::kbits_8,
  RFIDtoEEPROM_I2C::kbits_16,
  RFIDtoEEPROM_I2C::kbits_32,
  RFIDtoEEPROM_I2C::kbits_64,
  RFIDtoEEPROM_I2C::kbits_128,
  RFIDtoEEPROM_I2C::kbits_256,
  RFIDtoEEPROM_I2C::kbits_512,
  RFIDtoEEPROM_I2C::kbits_1024,
  RFIDtoEEPROM_I2C::kbits_2048
}
```

And use one of the enumerations below to set twiClock (Wire) Frequence:
```
{
  RFIDtoEEPROM_I2C::twiClock100kHz,
  RFIDtoEEPROM_I2C::twiClock400kHz
}
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

## Future Features

- Increase the number of recordable Cards (currently set to 255).
- Improve error handling.

## Limitations

- The Number of Bytes in the UID must be less than or equal to 16!
- The Number of recordable Cards is fixed at 255.

## License

MIT
