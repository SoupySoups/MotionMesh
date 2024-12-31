#include "joystick.h"

Joystick::Joystick(int xPin, int yPin, int rPin, int sensitivity = 400, bool doInvert = false, int deadZoneWidth = 0) {
    this->xPin = xPin;
    this->yPin = yPin;
    this->rPin = rPin;
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(rPin, INPUT);

    this->sensitivity = sensitivity;
    this->doInvert = doInvert;
    this->deadZoneWidth = deadZoneWidth;
    this->RdeadZoneWidth = deadZoneWidth;
}

int Joystick::OverSample(int pin, int samples = 10) {
    int raw  = 0;
    for  (byte n = 0; n < samples; n++) {
        raw += analogRead(pin);
        delay(1);
    }
    return raw / samples;
}

void Joystick::Calibrate() {
    this->calibratedRealX0 = OverSample(this->xPin);
    this->calibratedRealY0 = OverSample(this->yPin);
    this->calibratedRealR0 = OverSample(this->rPin);
}

bool Joystick::getInvert() {
    return this->doInvert;
}

int Joystick::getSensitivity() {
    return this->sensitivity;
}

void Joystick::setInvert(bool doInvert) {
    this->doInvert = doInvert;
}

void Joystick::setSensitivity(int sensitivity) {
    this->sensitivity = sensitivity;
}

void Joystick::setXRange(int minX, int maxX) {
    this->minX = minX;
    this->maxX = maxX;
}

void Joystick::setYRange(int minY, int maxY) {
    this->minY = minY;
    this->maxY = maxY;
}

void Joystick::setRRange(int minR, int maxR) {
    this->minR = minR;
    this->maxR = maxR;
}

JoystickData Joystick::read() {
    JoystickData data;

    if (lastSampleMs == -1) lastSampleMs = millis();
    long thisRead = millis();
    float dt = (thisRead - lastSampleMs) / 1000.0;
    lastSampleMs = thisRead;

    int rawX = OverSample(this->xPin);
    int rawY = OverSample(this->yPin);
    int rawR = OverSample(this->rPin);

    rawX = this->calibratedRealX0 - rawX;
    rawY = this->calibratedRealY0 - rawY;
    rawR = this->calibratedRealR0 - rawR;

    if (abs(rawX) < this->deadZoneWidth/2) rawX = 0;
    if (abs(rawY) < this->deadZoneWidth/2) rawY = 0;
    if (abs(rawR) < this->RdeadZoneWidth/2) rawR = 0;

    if (this->doInvert) {
        rawX = -rawX;
        rawY = -rawY;
        rawR = -rawR;
    }

    x = x + map(rawX, -512, 512, -sensitivity, sensitivity)*dt;
    y = y + map(rawY, -512, 512, -sensitivity, sensitivity)*dt;
    r = r + map(rawR, -512, 512, -sensitivity, sensitivity)*dt;

    data.x = constrain(x, minX, maxX);
    data.y = constrain(y, minY, maxY);
    data.r = constrain(r, minR, maxR);

    return data;
}

//     data->point.x += map(overSample(17), -512, 512, -speed, speed)*dt;
//     data->point.x = constrain(data->point.x, 0, 800);
//     data->point.y += map(overSample(18), -512, 512, -speed, speed)*dt;
//     data->point.y = constrain(data->point.y, 0, 480);

//     Serial.print("x: ");
//     Serial.print(data->point.x);
//     Serial.print(", y: ");
//     Serial.println(data->point.y);
// }