int i = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print("i Value: ");
    Serial.println(i);
    i += 1;

    delay(1000);
}
