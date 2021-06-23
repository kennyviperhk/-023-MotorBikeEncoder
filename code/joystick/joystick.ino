#include "HID-Project.h"

boolean debugMode = false;

bool isIncreasing = true;

int trickerPin = A0;
int trickerPinValue = 0;
int encoderPin = 7;
boolean isHomeSet = false;
boolean isTrigger = false;
long currMillis;
long prevMillis = 0;
long interval = 50;

int sensorValue;
float sensorValueToDegree;
int totalDegree = 360;
int selectedDegree = 120;
int homeDegree = 0;
int prevValue = 0;
int roundLargerThan360 = 0;
boolean isRound = false;
int middleLeftLevel, middleRightLevel, leftMostLevel, rightMostLevel, leftLevel, rightLevel;

void setup() {
  Serial.begin(115200);
  encoderSetup();
}



void loop() {
  currMillis = millis();
  sensorLoop();
  if (isHomeSet) {
    encoderLoop();
  }
}
