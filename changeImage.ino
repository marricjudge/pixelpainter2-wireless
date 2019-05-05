// CHANGE IMAGE
void changeImage() {
  int changeImageButtonState = 0;
  int lastchangeImageButtonState = 0;
  int currentchangeImageButtonState = 0;
  currentchangeImageButtonState = digitalRead(changeImagePin);

  if (currentchangeImageButtonState != lastchangeImageButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastchangeImageButtonState > debounceDelay)) {

    if (currentchangeImageButtonState != changeImageButtonState) {
      changeImageButtonState = currentchangeImageButtonState;
      if (changeImageButtonState == HIGH) {
        Serial.println("Image select button pressed");
        HC12.print("B");
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Next image selected");

        while (HC12.available()) {
          incomingByte = (HC12.read());      // Storing each incoming byte
          readBuffer += char(incomingByte); //Adding each byte together
          //Serial.println(readBuffer);
          //Serial.println("HC12 is available and buffer has been printed");
          Serial.print(readBuffer);
          lcd.setCursor(1, 2);
          lcd.print(readBuffer);

        }
      }
    }
  }
  lastchangeImageButtonState = currentchangeImageButtonState;

  readBuffer = "";
  while (HC12.available()) {
    incomingByte = (HC12.read());      // Storing each incoming byte
    readBuffer += char(incomingByte); //Adding each byte together

    if (readBuffer == "rbc") { //rbc = Reboot Confirmation
      Serial.println("Reboot confirmed from B");
    }
  }
} // END OF CHANGE IMAGE
