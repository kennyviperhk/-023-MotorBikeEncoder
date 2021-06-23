void encoderSetup() {
  Gamepad.begin();
}

void encoderLoop() {
  sensorValue = analogRead(encoderPin);
  sensorValueToDegree = map(sensorValue, 2, 1014, 0, 359.99);
  float bufferDegree = 3;
  float buf = prevValue - sensorValueToDegree;
  if (abs(buf) > bufferDegree && abs(buf) < selectedDegree) {

    if (buf < -bufferDegree) {
      isIncreasing = true;
      if (prevValue > 240 && !isRound) {
        roundLargerThan360 ++;
        isRound = true;
      }
    }
    else{
      isIncreasing = false;
      if (prevValue < 120 && roundLargerThan360 > 0  && !isRound) {
        roundLargerThan360 --;
        isRound = true;
      }
    }
  prevValue = sensorValueToDegree;
  } else {
    isRound = false;
  }


  sensorValueToDegree += (roundLargerThan360 * 360);
  if (sensorValueToDegree > totalDegree) {
    totalDegree = sensorValueToDegree;
  }
  if (homeDegree > 0) {
    sensorValueToDegree -= homeDegree;
    if (sensorValueToDegree < 0) {
      sensorValueToDegree = 0;
    }
  }
  float fixedDegree = map(sensorValueToDegree, 0, totalDegree, 0, 359);
  Gamepad.xAxis(levelMapping(round(fixedDegree)));
  Gamepad.write();

  Serial.print(sensorValueToDegree);
  Serial.print("\t");
  Serial.print(totalDegree);
  Serial.print("\t");
  Serial.print("isIncreasing : ");
  Serial.print(isIncreasing);
  Serial.print("\t");
  Serial.println(roundLargerThan360);
}

int levelMapping(int degreeValue)
{
  int levelValue;

  leftMostLevel = totalDegree - selectedDegree / 2;
  rightMostLevel = selectedDegree / 2;
  leftLevel = leftMostLevel + (selectedDegree / 5);
  rightLevel = rightMostLevel - (selectedDegree / 5);
  middleLeftLevel = totalDegree - ((selectedDegree / 5) / 2);
  middleRightLevel = ((selectedDegree / 5) / 2);

  if ( degreeValue > middleLeftLevel || degreeValue < middleRightLevel ) {
    levelValue = 180;
    int16_t degreeToJoystickValue = 0;
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > middleRightLevel && degreeValue < rightLevel ) {
    levelValue = 270;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > rightLevel && degreeValue < rightMostLevel ) {
    levelValue = totalDegree;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > leftLevel && degreeValue < middleLeftLevel ) {
    levelValue = 90;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > leftMostLevel && degreeValue < leftLevel ) {
    levelValue = 0;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > rightMostLevel && degreeValue < totalDegree / 2 ) {
    levelValue = totalDegree;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
  if ( degreeValue > totalDegree / 2 && degreeValue < leftMostLevel ) {
    levelValue = 0;
    int16_t degreeToJoystickValue = map(levelValue, 0, totalDegree, -32768, 32767);
    return degreeToJoystickValue;
    if (debugMode) {
      Serial.println(levelValue);
    }
  }
}
