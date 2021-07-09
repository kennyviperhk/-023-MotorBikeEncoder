void encoderSetup() {
  Gamepad.begin();
}

void encoderLoop() {
  sensorValue = analogRead(encoderPin);
  sensorValueToDegree = mapfloat(sensorValue * 1.0, 2.0, 1014.0, 0.0, 359.99);
  float bufferDegree = 10;
  float buf = prevValue - sensorValueToDegree;
  if (abs(buf) > bufferDegree) {
    /*
      if (sensorValueToDegree > 240 || sensorValueToDegree < 120) {
      isWithingChangingZone = true;
      } else {
      isWithingChangingZone = false;
      isRound = false;
      }
    */
    if (antiClockWise) {
      if (buf < -bufferDegree) {
        isIncreasing = true;
        relativeValue += bufferDegree;
        /*
          if (prevValue > 240 && !isRound && isWithingChangingZone) {
          roundLargerThan360 ++;
          isRound = true;
          }
        */
      }
      else {
        isIncreasing = false;
        if (relativeValue < bufferDegree) {
          relativeValue = 0;
        } else {
          relativeValue -= bufferDegree;
        }
        /*
          if (prevValue < 120 && roundLargerThan360 > 0  && !isRound && isWithingChangingZone) {
          roundLargerThan360 --;
          isRound = true;
          }
        */
      }
    } else {
      if (buf > -bufferDegree) {
        isIncreasing = true;
        relativeValue += bufferDegree;
        /*
          if (prevValue > 240 && !isRound && isWithingChangingZone) {
          roundLargerThan360 ++;
          isRound = true;
          }
        */
      }
      else {
        isIncreasing = false;
        if (relativeValue < bufferDegree) {
          relativeValue = 0;
        } else {
          relativeValue -= bufferDegree;
        }
        /*
          if (prevValue < 120 && roundLargerThan360 > 0  && !isRound && isWithingChangingZone) {
          roundLargerThan360 --;
          isRound = true;
          }
        */
      }
    }
    prevValue = sensorValueToDegree;
  }

  if (relativeValue > totalDegree) {
    totalDegree = relativeValue;
  }

  if (debugMode) {
    Serial.print("sensorValueToDegree : ");
    Serial.print(sensorValueToDegree);
    Serial.print("isIncreasing : ");
    Serial.print(isIncreasing);
    Serial.print("relativeValue : ");
    Serial.print(relativeValue);
    Serial.print("\t");
    Serial.print("totalDegree : ");
    Serial.print(totalDegree);
  }

  //float fixedDegree = map(sensorValueToDegree, 0, totalDegree, 0, 359.99);
  float correctedDegree;
/*
  if (sensorValueToDegree > 340 && !isIncreasing && prevCommand != 5) {
    sensorValueToDegree = 5;
  }else  if (sensorValueToDegree > 340 && isIncreasing) {
    sensorValueToDegree = 340;
  }
  if (sensorValueToDegree < 10 && isIncreasing) {
    sensorValueToDegree = 340;
  }*/

  if (sensorValueToDegree > 320 && prevCommand == 5) {
    sensorValueToDegree = 340;
  }
  if (sensorValueToDegree < 20 && prevCommand == 5) {
    sensorValueToDegree = 340;
  }

  if (sensorValueToDegree < 20 && prevCommand == 1) {
    sensorValueToDegree = 5;
  }
    if (sensorValueToDegree > 320 && prevCommand == 1) {
    sensorValueToDegree = 5;
  }

  //Gamepad.xAxis(levelMapping(sensorValueToDegree));
  Gamepad.releaseAll();
  Gamepad.press(dpadMapping(sensorValueToDegree));
  Gamepad.write();
}

int levelMapping(float degreeValue)
{
  int levelValue;

  leftMostLevel = 5;
  rightMostLevel = 355;
  selectedDegree = rightMostLevel;
  leftLevel = selectedDegree / 5;
  rightLevel = rightMostLevel - (selectedDegree / 5);
  middleLeftLevel = leftLevel + (selectedDegree / 5);
  middleRightLevel = rightLevel - (selectedDegree / 5);

  if ( degreeValue >= leftMostLevel && degreeValue < leftLevel ) {
    levelValue = 0;
    //int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
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


int dpadMapping(float degreeValue)
{
  int levelValue;
  int command;
  leftMostLevel = 5;
  rightMostLevel = 355;
  selectedDegree = rightMostLevel;
  leftLevel = selectedDegree / 5;
  rightLevel = rightMostLevel - (selectedDegree / 5);
  middleLeftLevel = leftLevel + (selectedDegree / 5);
  middleRightLevel = rightLevel - (selectedDegree / 5);
Serial.print("\t Zone: ");

  if ( degreeValue >= leftMostLevel && degreeValue < leftLevel ) {
    levelValue = 0;
    //int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    Serial.println("1");
    prevCommand = 1;
    return 1;
  }
  if ( degreeValue > leftLevel && degreeValue < middleLeftLevel ) {
    levelValue = 1;
    int16_t degreeToJoystickValue = map(levelValue, 0, 360, -32768, 32767);
    Serial.println("2");
    prevCommand = 2;
    return 2;
  }
  if ( degreeValue > middleLeftLevel && degreeValue < middleRightLevel ) {
    levelValue = 2;
    int16_t degreeToJoystickValue = 0;
    Serial.println("3");
    prevCommand = 3;
    return 3;
  }
  if ( degreeValue > middleRightLevel && degreeValue < rightLevel ) {
    levelValue = 3;

    Serial.println("4");
    prevCommand = 4;
    return 4;
  }
  if ( degreeValue > rightLevel && degreeValue <= rightMostLevel ) {
    levelValue = 4;

    Serial.println("5");
    prevCommand = 5;
    return 5;
  }
  Serial.println("NOT IN ANYTHING");

  return prevCommand;
}


float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
