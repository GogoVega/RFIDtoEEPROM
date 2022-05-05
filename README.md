# RFIDtoEEPROM

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

## Feature

- Compatibility with I2C EEPROM.

## Usage

This library is used for saving an RFID Code to your Arduino's **internal EEPROM** rather than your Code to avoid **showing your RFID Code**. To then check if the Code corresponds to a Code already registered.

## How To Use

Go to the Libraries Manager on [PlatformIO](https://platformio.org/platformio-ide) and search for `RFID to EEPROM`. Then you just have to install it in your project.

![PlatformIO](https://raw.githubusercontent.com/GogoVega/RFIDtoEEPROM/master/docs/platformio.png)

Or use `platformIO Core CLI` and paste the following command:

```bash
pio lib install "gogovega/RFID to EEPROM@^1.0.0"
```

## How It Works

This library contains several functions:
| Name | Description |
|---|---|
| `CardNumber()` | Returns the number of Cards already registered. |
| `SaveCard()` | Stores the RFID Code of a Card in the EEPROM. Returns `true` if the write succeeds. Otherwise returns `false` and restores the old Card. |
| `CardCheck()` | Checks if the Code received corresponds to a Code already stored in the EEPROM. Returns `true` if a Card matches. |
| `ClearCardNumber()` | Resets the number of recorded Cards to 0. |
| `EraseAllCards()` | Resets all Cards to 0. |
| `MaxCards()` | Returns the maximum number of recordable Cards. Currently **set to 255**. |

**Note:** The EEPROM memory has a specified life of 100,000 write/erase cycles, so you may need to be careful about how often you write to it.

## License

MIT
