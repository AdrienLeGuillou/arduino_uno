const int sensorPin = A0;
const float baselineTemp = 13.0;
const int firstLed = 2;
const int nLed = 3;

void setup() {
    Serial.begin(9600);

    for (int pinNumber = firstLed; pinNumber < firstLed + nLed; pinNumber++) {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, LOW);
    }
}

void loop() {
    int sensorVal = analogRead(sensorPin);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);

    float voltage = (sensorVal / 1024.0) * 5.0;
    Serial.print(", Volts: ");
    Serial.print(voltage);

    float temperature = (voltage - .5) * 100;
    Serial.print(", degrees C: ");
    Serial.println(temperature);

    int ledPat[3] = {LOW, LOW, LOW};
    if (temperature >= baselineTemp + 2.0) ledPat[0] = HIGH ;
    if (temperature >= baselineTemp + 4.0) ledPat[1] = HIGH ;
    if (temperature >= baselineTemp + 6.0) ledPat[2] = HIGH ;

    for (int i = 0; i < nLed; i++) {
        digitalWrite(firstLed + i, ledPat[i]);
    }

    delay(1000);
}
