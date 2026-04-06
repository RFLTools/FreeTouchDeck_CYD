/**
 * @brief This function presents the user with 4 points to touch and saves
          that data to a calibration file. For XPT2046 on CYD, we use a 
          simpler 2-point calibration to determine touch scaling.
 *
 * @param none
 *
 * @return none
 *
 * @note If USECAPTOUCH is defined we do not need to calibrate touch
 */

#if !defined(USECAPTOUCH)

// Calibration data structure for XPT2046
struct TouchCalibration {
  int16_t x_min;
  int16_t x_max;
  int16_t y_min;
  int16_t y_max;
};

TouchCalibration touchCal;

void touch_calibrate()
{
  uint8_t calDataOK = 0;

  // check if calibration file exists and size is correct
  if (FILESYSTEM.exists(CALIBRATION_FILE))
  {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      FILESYSTEM.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = FILESYSTEM.open(CALIBRATION_FILE, "r");
      if (f)
      {
        if (f.readBytes((char *)&touchCal, sizeof(TouchCalibration)) == sizeof(TouchCalibration))
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL)
  {
    // calibration data valid - already loaded into touchCal
    Serial.println("[INFO]: Touch calibration loaded from file");
    Serial.printf("[INFO]: X: %d to %d, Y: %d to %d\n", touchCal.x_min, touchCal.x_max, touchCal.y_min, touchCal.y_max);
  }
  else
  {
    // data not valid so recalibrate using 2-point method
    // Get actual screen dimensions after rotation
    int screenW = tft.width();
    int screenH = tft.height();
    
    Serial.printf("[INFO]: Starting touch calibration\n");
    Serial.printf("[INFO]: Display rotation: %d\n", tft.getRotation());
    Serial.printf("[INFO]: Screen dimensions: %dx%d\n", screenW, screenH);
    
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 20);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch calibration");
    tft.printf("Screen: %dx%d\n", screenW, screenH);
    tft.printf("Rotation: %d\n", tft.getRotation());
    tft.println("Touch each circle");

    if (REPEAT_CAL)
    {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false");
      tft.println("to stop this!");
    }

    delay(2000);

    // Calculate calibration circle positions based on actual screen size
    int margin = 20;
    int x1 = margin;
    int y1 = margin;
    int x2 = screenW - margin;
    int y2 = screenH - margin;

    // Calibration point 1 - top left
    tft.fillScreen(TFT_BLACK);
    tft.fillCircle(x1, y1, 10, TFT_MAGENTA);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(x1 + 20, y1 - 5);
    tft.println("Touch circle");
    
    Serial.printf("[INFO]: Circle 1 at (%d, %d)\n", x1, y1);
    
    // Wait for touch
    while (!touchscreen.touched()) { delay(10); }
    TS_Point p1 = touchscreen.getPoint();
    Serial.printf("[INFO]: Raw touch 1: x=%d, y=%d\n", p1.x, p1.y);
    delay(200); // Debounce
    while (touchscreen.touched()) { delay(10); } // Wait for release

    // Calibration point 2 - bottom right
    tft.fillScreen(TFT_BLACK);
    tft.fillCircle(x2, y2, 10, TFT_MAGENTA);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(x2 - 100, y2 - 5);
    tft.println("Touch circle");
    
    Serial.printf("[INFO]: Circle 2 at (%d, %d)\n", x2, y2);
    
    // Wait for touch
    while (!touchscreen.touched()) { delay(10); }
    TS_Point p2 = touchscreen.getPoint();
    Serial.printf("[INFO]: Raw touch 2: x=%d, y=%d\n", p2.x, p2.y);
    delay(200); // Debounce
    while (touchscreen.touched()) { delay(10); } // Wait for release

    // Calculate calibration based on 2 points
    touchCal.x_min = p1.x;
    touchCal.x_max = p2.x;
    touchCal.y_min = p1.y;
    touchCal.y_max = p2.y;

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(20, 20);
    tft.setTextFont(2);
    tft.println("Calibration complete!");
    tft.println("");
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.println("Set REPEAT_CAL");
    tft.println("to false in code");
    tft.println("to stop recalibrating");
    
    Serial.printf("[INFO]: Calibration: X: %d to %d, Y: %d to %d\n", 
                  touchCal.x_min, touchCal.x_max, touchCal.y_min, touchCal.y_max);

    delay(2000);

    // store data
    File f = FILESYSTEM.open(CALIBRATION_FILE, "w");
    if (f)
    {
      f.write((const unsigned char *)&touchCal, sizeof(TouchCalibration));
      f.close();
      Serial.println("[INFO]: Calibration saved to file");
    }
  }
}

// Helper function to get calibrated touch coordinates
bool getTouch(uint16_t *x, uint16_t *y) {
  if (touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    
    // Debug: print raw touch values (comment out after testing)
    // Serial.printf("[TOUCH] Raw: x=%d, y=%d, z=%d\n", p.x, p.y, p.z);
    
    // Map raw coordinates to screen coordinates using calibration
    *x = map(p.x, touchCal.x_min, touchCal.x_max, 0, SCREEN_WIDTH);
    *y = map(p.y, touchCal.y_min, touchCal.y_max, 0, SCREEN_HEIGHT);
    
    // Constrain to screen bounds
    *x = constrain(*x, 0, SCREEN_WIDTH);
    *y = constrain(*y, 0, SCREEN_HEIGHT);
    
    // Debug: print mapped touch values (comment out after testing)
    // Serial.printf("[TOUCH] Mapped: x=%d, y=%d\n", *x, *y);
    
    return true;
  }
  return false;
}

#endif //!defined(USECAPTOUCH)
