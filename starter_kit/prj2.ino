int blink = 0;
int toggled = 0;

struct Button {
  int state = 0;
  int change = 1;
}

void setup() {
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop() {
    int switchState = 0;
    switchState = digitalRead(2);

    if (switchState == HIGH) {
        if (!toggled) {
            blink = (blink + 1) % 3;
            toggled = 1;
        }
    } else {
        toggled = 0;
    }

    if (blink == 0) {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    } else if (blink == 1) {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        delay(250);
    } else {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        delay(250);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);
        delay(250);
    }
}


