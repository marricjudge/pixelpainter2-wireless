void sendSpeed() {
  int speedButtonState      =   analogRead(speedPin);
  Serial.print("Set speed: ");
  Serial.print(speedButtonState);
  HC12.print(speedButtonState);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Speed sent: ");
  lcd.setCursor(13, 1);
  lcd.print(speedButtonState);

  Serial.print(" - Command sent: ");
  Serial.println(speedButtonState); //Print Command in serial monitor
  readBuffer = "";
  int confirmFlag = 1;

  while (HC12.available()) {
    incomingByte = (HC12.read());      // Storing each incoming byte
    readBuffer += char(incomingByte); //Adding each byte together
    //Serial.println(readBuffer);
    //Serial.println("HC12 is available and buffer has been printed");
  }
}
