// This is a test project to validate the circuitry
//  8 led to represent a byte, connected to pins below
const int ledPins[8] = {6, 7, 8, 9, 10, 13, 12, 11};
int ledByte = 0;

// 3 button that do +1 , *2 and reset the byte value when released
const int btnPins[3] = {3, 4, 5};
int btnState[3] = {0, 0, 0};
int btnLast[3] = {0, 0, 0};

// 4 of the leds are on pwm pins
// a potentiometer override the value of the leds when > 0
const int pwmPins[4] = {6, 9, 10, 11};
const int potenPin = A0;
int pwmVal = 0;

// function turning the LEDs on and off
void setLeds(int ledByte, const int* ledPins) {
    for (int l = 0; l < 8; l ++) {
        int bitL = ledByte & (1 << l);
        digitalWrite(ledPins[l], bitL);
    }
}

// function setting the pwm LEDs
void setPwmLeds(int ledByte, const int* pwmPins, int pwmVal) {
    for (int p = 0; p < 4; p ++) {
        analogWrite(pwmPins[p], pwmVal);
    }
}

void setup() {
    for (int l = 0; l < 8; l++) {
        pinMode(ledPins[l], OUTPUT);
    }

    for (int b = 0; b < 3; b++) {
        pinMode(btnPins[b], INPUT);
    }
}

void loop() {
    // 0-1024 -> 0-255
    pwmVal = analogRead(potenPin) / 4;

    for (int b = 0; b < 3; b++) {
        btnState[b] = digitalRead(btnPins[b]);
    }

    // +1 released this cycle
    if (btnState[0] == LOW && btnLast[0] == HIGH) {
        ledByte += 1;
    }
    // x2 released this cycle
    if (btnState[1] == LOW && btnLast[1] == HIGH) {
        ledByte *= 2;
    }
    // reset released this cycle
    if (btnState[2] == LOW && btnLast[2] == HIGH) {
        ledByte = 0;
    }

    // must be represented by 1 byte
    ledByte = ledByte % 256;

    // use byte repr or pwm
    if (pwmVal > 0) {
        setPwmLeds(ledByte, pwmPins, pwmVal);
    } else {
        setLeds(ledByte, ledPins);
    }

    for (int b = 0; b < 3; b++) {
        btnLast[b] = btnState[b];
    }
}

