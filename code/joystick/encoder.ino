void encoderSetup() {
  Gamepad.begin();
}

void encoderLoop() {
  sensorValue = analogRead(encoderPin);
  sensorValueToDegree = mapfloat(sensorValue * 1.0, 2.0, 1014.0, 0.0, 359.99);
  float bufferDegree = 3;
  float buf = prevValue - sensorValueToDegree;
  if (abs(buf) > bufferDegree) {
    if (sensorValueToDegree > 240 || sensorValueToDegree < 120) {
      isWithingChangingZone = true;
    } else {
      isWithingChangingZone = false;
      isRound = false;
    }
    if (buf < -bufferDegree) {
      isIncreasing = true;
      relativeValue += bufferDegree;
      if (prevValue > 240 && !isRound && isWithingChangingZone) {
        roundLargerThan360 ++;
        isRound = true;
      }
    }
    else {
      isIncreasing = false;
      if (relativeValue < bufferDegree) {
        relativeValue = 0;
      } else {
        relativeValue -= bufferDegree;
      }
      if (prevValue < 120 && roundLargerThan360 > 0  && !isRound && isWithingChangingZone) {
        roundLargerThan360 --;
        isRound = true;
      }
    }
    prevValue = sensorValueToDegree;
  }

  if (relativeValue > totalDegree) {
    totalDegree = relativeValue;
  }

  if (debugMode) {
    Serial.print("relativeValue : ");
    Serial.print(relativeValue);
    Serial.print("\t");
    Serial.print("totalDegree : ");
    Serial.print(totalDegree);
  }

  float fixedDegree = map(relativeValue, 0, totalDegree, 0, 359.99);
  Gamepad.xAxis(levelMapping(fixedDegree));
  Gamepad.write();
}

int levelMapping(float degreeValue)
{
  int levelValue;

  leftMostLevel = 0;
  rightMostLevel = selectedDegree;
  leftLevel = selectedDegree / 5;
  rightLevel = rightMostLevel - (selectedDegree / 5);
  middleLeftLevel = leftLevel + (selectedDegree / 5);
  middleRightLevel = rightLevel - (selectedDegree / 5);

  if ( degreeValue >= leftMostLevel && degreeValue < leftLevel ) {
    levelValue = 0;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    if (debugMode) {
      Serial.print("\t");
      Serial.print("leftMostLevel");
      Serial.print("\t");
      Serial.print("JoyStickValue : ");
      Serial.println(levelValue);
    }
    return degreeToJoystickValue;
  }
  if ( degreeValue > leftLevel && degreeValue < middleLeftLevel ) {
    levelValue = 90;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    if (debugMode) {
      Serial.print("\t");
      Serial.print("leftLevel");
      Serial.print("\t");
      Serial.print("JoyStickValue : ");
      Serial.println(levelValue);
    }
    return degreeToJoystickValue;
  }
  if ( degreeValue > middleLeftLevel && degreeValue < middleRightLevel ) {
    levelValue = 180;
    int16_t degreeToJoystickValue = 0;
    if (debugMode) {
      Serial.print("\t");
      Serial.print("middleLevel");
      Serial.print("\t");
      Serial.print("JoyStickValue : ");
      Serial.println(levelValue);
    }
    return degreeToJoystickValue;
  }
  if ( degreeValue > middleRightLevel && degreeValue < rightLevel ) {
    levelValue = 270;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    if (debugMode) {
      Serial.print("\t");
      Serial.print("rightLevel");
      Serial.print("\t");
      Serial.print("JoyStickValue : ");
      Serial.println(levelValue);
    }
    return degreeToJoystickValue;
  }
  if ( degreeValue > rightLevel && degreeValue <= rightMostLevel ) {
    levelValue = 360;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    if (debugMode) {
      Serial.print("\t");
      Serial.print("rightMostLevel");
      Serial.print("\t");
      Serial.print("JoyStickValue : ");
      Serial.println(levelValue);
    }
    return degreeToJoystickValue;
  }
}


float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
