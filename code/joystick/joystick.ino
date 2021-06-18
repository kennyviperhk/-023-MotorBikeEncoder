/* Library info: https://www.arduino.cc/reference/en/libraries/hid-project/ */

#include "HID-Project.h"

int sensorPin = 7;
long prevMillis = 0;
long interval = 10;
int totalDegree = 120;
int middleLeftLevel, middleRightLevel, leftMostLevel, rightMostLevel, leftLevel, rightLevel;

void setup() {
  Serial.begin(115200);
  Gamepad.begin();
  leftMostLevel = 360 - totalDegree / 2;
  rightMostLevel = totalDegree / 2;
  leftLevel = leftMostLevel + (totalDegree / 5);
  rightLevel = rightMostLevel - (totalDegree / 5);
  middleLeftLevel = 360 - ((totalDegree / 5) / 2);
  middleRightLevel = ((totalDegree / 5) / 2);
}



void loop() {
  long currMillis = millis();
  if (currMillis - prevMillis > interval) {
    prevMillis = currMillis;
    int sensorValue = analogRead(sensorPin);
    int sensorValueToDegree = map(sensorValue, 2, 1014, 0, 360);
    Serial.println(levelMapping(sensorValueToDegree));
    Gamepad.xAxis(levelMapping(sensorValueToDegree));
    Gamepad.write();
  }
}


int levelMapping(int degreeValue)
{
  int levelValue;
  if ( degreeValue > middleLeftLevel || degreeValue < middleRightLevel ) {
    levelValue = 180;
    int16_t degreeToJoystickValue = 0;
    return degreeToJoystickValue;
  }
  if ( degreeValue > middleRightLevel && degreeValue < rightLevel ) {
    levelValue = 270;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
  if ( degreeValue > rightLevel && degreeValue < rightMostLevel ) {
    levelValue = 360;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
  if ( degreeValue > leftLevel && degreeValue < middleLeftLevel ) {
    levelValue = 90;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
  if ( degreeValue > leftMostLevel && degreeValue < leftLevel ) {
    levelValue = 0;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
  if ( degreeValue > rightMostLevel && degreeValue < 180 ) {
    levelValue = 360;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
  if ( degreeValue > 180 && degreeValue < leftMostLevel ) {
    levelValue = 0;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    return degreeToJoystickValue;
  }
}
