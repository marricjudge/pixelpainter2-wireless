/* ELEMENTS OF THE FUTURE
   LIGHTPAINTING PROJECT

   for SM3733 Sem B 2018/19
   by Skyguy Mok and Marius Richter

   Code written by Marius Richter

   Code Part A: Ground Control Station

   Latest Edit: 05. May 2019
*/

const int playPin        =  7;    
const int setValuesPin   =  6;
const int speedPin       =  A0;
const int brightnessPin  =  A1;
const int changeImagePin =  5;
const int rebootPin      =  4;
const int HC12TXpin      =  10;
const int HC12RXpin      =  11;
const int ledPin         =  13; 

#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial HC12(HC12TXpin, HC12RXpin); // HC-12 TX Pin, HC-12 RX Pin
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


byte incomingByte;
String readBuffer = "";

int playButtonState;         // variable for reading the pushbutton status
int lastPlayButtonState = 0;
int currentPlayButtonState = 0;

int BsetupFlag = 1;
int setValueFlag = 0;
int ledState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;



void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  lcd.begin(20, 4);

  // initialize pins
  pinMode(playPin, INPUT);
  pinMode(setValuesPin, INPUT);
  pinMode(speedPin, INPUT);
  pinMode(brightnessPin, INPUT);
  pinMode(changeImagePin, INPUT);
  pinMode(rebootPin, INPUT);
  pinMode(ledPin, OUTPUT);


  Serial.println("A: Ground station setup successful");
  lcd.setCursor(0, 0);
  lcd.print("Pixelpainter V2.0.3");

  Bsetup(); //run the setup for the receiver device "B"

  lcd.setCursor(0, 1);
  lcd.print("System setup successful");
  delay(1);
  lcd.setCursor(0, 3);
  lcd.print("Press any button");


} // End of void setup()


void loop() {

  if (HC12.available()) {        // If HC-12 has data
    incomingByte = (HC12.read());      // Storing each incoming byte
    readBuffer += char(incomingByte); //Adding each byte together
  }
  delay(100);
  while (Serial.available()) {      // If Serial monitor has data
    HC12.write(Serial.read());      // Send that data to HC-12
  }

  if (readBuffer == "Conf") { //When On-Board Station is ready it will send the number 1
    Serial.println("B: On Board station setup successful");
    lcd.setCursor(0, 3);
    lcd.print("Remote confirmed");
    readBuffer = ""; // Clean the buffer
  }

  currentPlayButtonState = digitalRead(playPin);

  if (currentPlayButtonState != lastPlayButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastPlayButtonState > debounceDelay)) {

    if (currentPlayButtonState != playButtonState) {
      playButtonState = currentPlayButtonState;
      if (playButtonState == HIGH) {
        Serial.println("-----------------------------");
        Serial.println("Play button pressed");
        sendSpeed(); //sent Speed function
        HC12.print("A"); //Print function to  receiver
        Serial.println("Command sent: Play Image");
        lcd.setCursor(0, 0);
        lcd.print("- - Play  sent - - ");

        readBuffer = ""; //Clear the buffer
        int confirmFlag = 1;

        while (HC12.available()) {
          incomingByte = (HC12.read());      // Storing each incoming byte
          readBuffer += char(incomingByte); //Adding each byte together

          if (readBuffer == "Conf") {
            Serial.println("Command confirmed from B");
            confirmFlag = 0;
          }

        }

        Serial.println("-----------------------------");
      }
    }
  }
  lastPlayButtonState = currentPlayButtonState;

  changeImage(); //Change Image Button function

  speedAndBrightnessSet(); //Set Speed and Brightness button function

  reboot(); //Reboot button function 

} // End of void loop()
