// REBOOT

void reboot() {
  int rebootButtonState = 0;
  rebootButtonState = digitalRead(rebootPin);

  if (rebootButtonState == HIGH) {

    Serial.print(rebootButtonState);
    Serial.println("both buttons");

    HC12.print("C");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reboot sent!");

    int brightnessButtonState      =   analogRead(brightnessPin);
    Serial.print("Set brightness: ");
    Serial.print(brightnessButtonState);
    delay(100);
    HC12.print(brightnessButtonState);

    lcd.setCursor(0, 2);
    lcd.print("Sent brightness ");
    lcd.setCursor(16, 2);
    lcd.print(brightnessButtonState);

  }
}
