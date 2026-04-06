# FreeTouchDeck for CYD (Cheap Yellow Display)

This project is based on the excellent [FreeTouchDeck by Dustin Watts](https://github.com/DustinWatts/FreeTouchDeck), but has been revised and adapted to work with the CYD (Cheap Yellow Display) and built using PlatformIO instead of the Arduino IDE.

## About This Fork

The original FreeTouchDeck project provides a Bluetooth macro keypad using an ESP32, touchscreen, and BLE to interface with Windows/macOS/Linux. This fork maintains that functionality while specifically targeting the popular CYD (ESP32-2432S028) hardware and using PlatformIO for easier dependency management and building.

### Key Changes from Original:
- Configured for CYD (ESP32-2432S028) hardware
- Built with PlatformIO instead of Arduino IDE
- Pre-configured TFT_eSPI settings for CYD
- Simplified setup process with platformio.ini configuration

## Installation

### Prerequisites
- [PlatformIO](https://platformio.org/) installed (either as CLI or VS Code extension)
- A CYD (ESP32-2432S028) board
- USB cable for programming

### Building and Uploading

1. Clone this repository:
   ```bash
   git clone <repository-url>
   cd FreeTouchDeck_CYD
   ```

2. Open the project in PlatformIO (or navigate to the directory in terminal)

3. Build and upload:
   ```bash
   pio run --target upload
   ```

4. Upload the filesystem (SPIFFS):
   ```bash
   pio run --target uploadfs
   ```

### Configuration

The project comes pre-configured for CYD hardware. All necessary settings are in the `platformio.ini` file and the TFT_eSPI library is configured automatically for the CYD display.

## Helper App

Dustin Watts created a helper app for Windows/macOS/Linux that will help you start applications, run scripts and can auto-switch FreeTouchDeck to a page you choose when an application comes in to focus. You can find it here: https://github.com/DustinWatts/FreeTouchDeck-Helper

## Supported Hardware

This fork specifically targets:
- **ESP32-2432S028** (CYD - Cheap Yellow Display)
  - 2.8" TFT LCD (320x240)
  - ILI9341 driver
  - XPT2046 resistive touch controller
  - Built-in ESP32

### Original FreeTouchDeck Hardware

For the original FreeTouchDeck project by Dustin Watts, see:
- [Original FreeTouchDeck Repository](https://github.com/DustinWatts/FreeTouchDeck)
- Supports ESP32 DEVKIT V1 with 3.5" ILI9488 displays
- Supports ESP32 TouchDown with capacitive touch

For other hardware variants and community forks, visit the [original FreeTouchDeck repository](https://github.com/DustinWatts/FreeTouchDeck). 

## Library Dependencies

All dependencies are automatically managed by PlatformIO through the `platformio.ini` file. The main libraries include:

- TFT_eSPI - Display driver
- ESP32-BLE-Keyboard - Bluetooth HID functionality
- ESPAsyncWebServer - Web configuration interface
- AsyncTCP - Async networking
- ArduinoJson - JSON parsing

No manual library installation is required when using PlatformIO.

## TFT_eSPI Configuration

Unlike the original project, this fork automatically configures TFT_eSPI for the CYD hardware using PlatformIO's build flags. No manual editing of `User_Setup.h` is required. The display and touch controller settings are defined in `platformio.ini`.

## Credits

This project is based on [FreeTouchDeck by Dustin Watts](https://github.com/DustinWatts/FreeTouchDeck). All credit for the original concept, design, and implementation goes to Dustin Watts.

### Support the Original Creator

If you find this project useful, please consider supporting Dustin Watts:

| Platform | Link|
|:-----:|:-----|
| [<img src="https://github.com/DustinWatts/small_logos/blob/main/twitter_logo.png" alt="Twitter" width="24"/>](https://twitter.com/dustinwattsnl "Follow on Twitter") | Follow on Twitter: [@dustinwattsnl](https://twitter.com/dustinwattsnl)|
| [<img src="https://github.com/DustinWatts/small_logos/blob/main/youtube_logo.png" alt="YouTube" width="32"/>](https://www.youtube.com/dustinwatts "Subscribe on YouTube") | Subscribe on YouTube: [/dustinWatts](https://www.youtube.com/dustinwatts) |
| [<img src="https://github.com/DustinWatts/small_logos/blob/main/patreon_logo.png" alt="Patreon" width="32"/>](https://www.patreon.com/dustinwatts) | Support on Patreon: https://www.patreon.com/dustinwatts |
| [<img src="https://github.com/DustinWatts/small_logos/blob/main/paypalme_logo.png" alt="PayPal.me" width="32"/>](https://www.paypal.me/dustinwattsnl) | Donate via PayPal: https://www.paypal.me/dustinwattsnl |

## Get Help

For help with the original FreeTouchDeck project, join Dustin's Discord server: https://discord.gg/RE3XevS

For issues specific to this CYD/PlatformIO fork, please open an issue in this repository.

## License

This project maintains the same license as the original FreeTouchDeck project.
