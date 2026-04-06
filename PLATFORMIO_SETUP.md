# PlatformIO Setup Guide for FreeTouchDeck

This project has been converted from Arduino IDE to PlatformIO structure.

## Project Structure

```
FreeTouchDeck/
├── platformio.ini          # PlatformIO configuration
├── src/                    # Source files
│   ├── main.cpp           # Main program (formerly FreeTouchDeck.ino)
│   └── *.h                # Header files
├── data/                   # SPIFFS/LittleFS filesystem data
│   ├── config/
│   ├── logos/
│   └── *.htm, *.js, etc.
└── user_setup.h Examples/  # TFT_eSPI configuration examples
```

## Getting Started

### 1. Install PlatformIO

If you haven't already, install PlatformIO:
- **VS Code**: Install the PlatformIO IDE extension
- **CLI**: `pip install platformio`

### 2. Configure TFT_eSPI Display Settings

**IMPORTANT**: You must configure TFT_eSPI for your specific display hardware.

The TFT_eSPI library needs a `User_Setup.h` file configured for your display. You have two options:

#### Option A: Configure in .platformio directory (Recommended)
After first build, edit the file:
```
.pio/libdeps/esp32dev/TFT_eSPI/User_Setup.h
```

Copy the appropriate settings from the `user_setup.h Examples` folder.

#### Option B: Use build flags in platformio.ini
Add your display configuration as build flags in `platformio.ini`. See the examples folder for reference.

### 3. Select Your Hardware Environment

Edit `platformio.ini` and set the appropriate environment:

- **ESP32 (default)**: `default_envs = esp32dev`
- **ESP32-S3**: `default_envs = esp32s3`

### 4. Configure Optional Features

In `src/main.cpp`, uncomment the defines for your hardware:

```cpp
// For capacitive touch (ESP32 TouchDown)
#define USECAPTOUCH

// For ESP32-S3
#define ESP32TouchDownS3

// For USB HID (boards with native USB)
#define USEUSBHID

// Custom I2C pins for capacitive touch
#define CUSTOM_TOUCH_SDA 17
#define CUSTOM_TOUCH_SCL 18

// Sleep/wake functionality
#define touchInterruptPin GPIO_NUM_27

// Piezo buzzer
#define speakerPin 26

// NimBLE library (lighter BLE implementation)
#define USE_NIMBLE
```

### 5. Build the Project

```bash
# Build
pio run

# Upload firmware
pio run --target upload

# Upload filesystem (SPIFFS)
pio run --target uploadfs

# Monitor serial output
pio device monitor
```

Or use the PlatformIO IDE buttons in VS Code.

## Library Dependencies

All dependencies are automatically managed by PlatformIO (defined in `platformio.ini`):

- TFT_eSPI (display driver)
- Adafruit GFX Library
- ArduinoJson v6
- ESP32-BLE-Keyboard
- ESPAsyncWebServer
- AsyncTCP
- FT6236 (for capacitive touch - optional)

## Upload Filesystem Data

The `data/` folder contains web interface files and configuration. Upload it to SPIFFS:

```bash
pio run --target uploadfs
```

## Troubleshooting

### Build Errors Related to TFT_eSPI
- Make sure you've configured `User_Setup.h` in the TFT_eSPI library
- Check that your pin definitions match your hardware
- Verify `USER_SETUP_LOADED` is defined

### BLE Keyboard Issues
- For ESP32-S3 or boards with native USB, uncomment `#define USEUSBHID`
- If using NimBLE library, uncomment `#define USE_NIMBLE`

### Upload Fails
- Check USB cable and driver installation
- Try reducing upload speed in `platformio.ini`
- Press BOOT button on ESP32 during upload if needed

## Additional Resources

- [PlatformIO Documentation](https://docs.platformio.org/)
- [FreeTouchDeck GitHub](https://github.com/DustinWatts/FreeTouchDeck)
- [TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI)

## Migration Notes

This project was converted from Arduino IDE structure:
- `FreeTouchDeck.ino` → `src/main.cpp`
- All `.h` files moved to `src/`
- `data/` folder remains in root (used for filesystem upload)
- Dependencies now managed via `platformio.ini` instead of manual installation
