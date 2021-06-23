void sensorLoop() {
  trickerPinValue = analogRead(trickerPin);
  if (trickerPinValue > 900 && !isTrigger) {

    if (!isHomeSet) {
      sensorValue = analogRead(encoderPin);
      sensorValueToDegree = map(sensorValue, 2, 1014, 0, 360);
      homeDegree = sensorValueToDegree;
      isHomeSet = true;
      Serial.print("SetHome: ");
      Serial.println(homeDegree);
    }
    isTrigger = true;
    Serial.println("isTrigger");
  }

  if (trickerPinValue < 900)
  {
    isTrigger = false;
  }
}
