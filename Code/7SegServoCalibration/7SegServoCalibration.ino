// https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

//Segment LuxorPart: 3, 600,200

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "ServoCalibrationValues.h"

#define PWMFrequency 50 // SG90 uses 50Hz
#define ON 1
#define OFF 0
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(&Wire, 0x40);

int seg = 0; 
uint16_t offValue = 0;
uint16_t onValue = 0;

uint16_t seg_state[2] = {offValue, onValue};
bool debug = 1; 
uint8_t enablePin = 19;
bool state = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  pinMode(enablePin, OUTPUT);  
  pwm.begin();
  pwm.setPWMFreq(PWMFrequency);
  //Wire.setClock(400000);
  Serial.println("Initialization Complete");
  digitalWrite(enablePin,LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String incommingString = Serial.readString();
    parseString(incommingString);
    state = 1; 
  }

  if (state) {
    Serial.println("Servo ON");
    setServo(seg,seg_state,ON);
    delay(1000);
    Serial.println("Servo OFF");
    setServo(seg,seg_state,OFF);
    delay(1000);   
    Serial.println("Servo ON");
    setServo(seg,seg_state,ON);
    delay(1000);
    state = 0;
  }

  delay(1000);

}

void parseString(String Data) {
  int i = 0;
  String aquiredSegment = "";
  String onString = "";
  String offString = "";
  while (Data[i] != ',') {
    aquiredSegment += Data[i];
    i++;
  }
  i++;
  while (Data[i] != ',') {
    onString += Data[i];
    i++;
  }
  i++;

  while (Data[i] != '\n') {
    offString += Data[i];
    i++;
  }
  seg = aquiredSegment.toInt();
  onValue = onString.toInt();
  offValue = offString.toInt();
  seg_state[0] = offValue;
  seg_state[1] = onValue;
  if (debug) {
    Serial.print("Segment ");
    Serial.print(aquiredSegment);
    Serial.print("\t");
    Serial.print("On ");
    Serial.print(onString);
    Serial.print("\t");
    Serial.print("Off ");
    Serial.println(offString);
  }
}

void setServo(uint8_t segment, uint16_t values[2], bool state) {
  pwm.setPWM(segment, 0, values[state]);
}
