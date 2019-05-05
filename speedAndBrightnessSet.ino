//SET SPEED AND BRIGHTNESS
void speedAndBrightnessSet() {
  int setValuesButtonState;
  int lastSetValueButtonState = 0;
  int currentSetValueButtonState = 0;

  int speedButtonState = 0;
  speedButtonState      =   analogRead(speedPin);

  int brightnessButtonState = 0;
  brightnessButtonState =   analogRead(brightnessPin);

  currentSetValueButtonState = digitalRead(setValuesPin);

  if (currentSetValueButtonState != lastSetValueButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastSetValueButtonState > debounceDelay)) {

    if (currentSetValueButtonState != setValuesButtonState) {
      setValuesButtonState = currentSetValueButtonState;
      if (setValuesButtonState == HIGH) {
        //ledState = !ledState;
        Serial.print("Speed is set to: ");
        Serial.println(speedButtonState);
        //HC12.write(speedButtonState);
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Speed set: ");
        lcd.setCursor(16, 1);
        lcd.print(speedButtonState);
        Serial.print("Brightness is set to: ");
        Serial.println(brightnessButtonState);
        lcd.setCursor(0, 2);
        lcd.print("Brightness set: ");
        lcd.setCursor(16, 2);
        lcd.print(brightnessButtonState);
        //HC12.write(brightnessButtonState);
      }
    }
  }
  lastSetValueButtonState = currentSetValueButtonState;
} // END OF SPEED AND BRIGHTNESS
