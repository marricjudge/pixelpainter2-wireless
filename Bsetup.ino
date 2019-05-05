int rebootCounter = 0;
void Bsetup() {
  if (BsetupFlag == true) { //Checks and waits it B is ready

    int brightnessButtonState      =   analogRead(brightnessPin);
    Serial.print("Set brightness: ");
    Serial.print(brightnessButtonState);
    HC12.print(brightnessButtonState);

    Serial.print(" - Command sent: ");
    Serial.println(brightnessButtonState); //Print Command in serial monitor
    readBuffer = "";

    lcd.setCursor(0, 2);
    lcd.print("Sent brightness ");
    lcd.setCursor(16, 2);
    lcd.print(brightnessButtonState);

    while (HC12.available()) {       // If HC-12 has data
      incomingByte = (HC12.read());      // Storing each incoming byte
      readBuffer += char(incomingByte); //Adding each byte together
      Serial.print(readBuffer);
      if (readBuffer = 9) { //When On-Board Station is ready it will send the number 1
        Serial.println("B: On Board station setup successful");
        lcd.clear();
        lcd.setCursor(3, 3);
        lcd.print("Remote success");
        BsetupFlag = false; //Disables setup mode and jumps into the main function
        readBuffer = ""; // Clean the buffer
      }
    }
  }
}
