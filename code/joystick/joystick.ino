#include "HID-Project.h"

boolean debugMode = true;

boolean antiClockWise = true;
bool isIncreasing = true;

int trickerPin = A0;
int trickerPinValue = 0;
int encoderPin = 7;
boolean isHomeSet = false;
boolean isTrigger = false;
long currMillis;
long prevMillis = 0;
long interval = 50;

float sensorValue;
float sensorValueToDegree;
int selectedDegree = 360;
int totalDegree = 90;
int homeDegree = 0;
int prevValue = 0;
int roundLargerThan360 = 0;
float relativeValue = 0;
boolean isWithingChangingZone = false;
boolean isRound = false;
float middleLeftLevel, middleRightLevel, leftMostLevel, rightMostLevel, leftLevel, rightLevel;

void setup() {
  Serial.begin(115200);
  encoderSetup();
}



void loop() {
  currMillis = millis();
  if (isHomeSet) {
    encoderLoop();
  } else {
    sensorLoop();
  }
}
