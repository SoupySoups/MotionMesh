# pragma once
#include <limits.h>
#include <Arduino.h>

typedef struct {
    int x;
    int y;
    int r;
} JoystickData;

class Joystick {
private:
    int x = 400;
    int y = 240;
    int r = 512;

    int xPin;
    int yPin;
    int rPin;

    int sensitivity;
    bool doInvert;
    int deadZoneWidth;
    int RdeadZoneWidth;

    int minX = INT_MIN;
    int maxX = INT_MAX;
    int minY = INT_MIN;
    int maxY = INT_MAX;
    int minR = INT_MIN;
    int maxR = INT_MAX;

    int calibratedRealX0;
    int calibratedRealY0;
    int calibratedRealR0;

    long lastSampleMs = -1;

    int OverSample(int pin, int samples);
public:
    Joystick(int xPin, int yPin, int rPin, int sensitivity, bool doInvert, int deadZoneWidth);
    void Calibrate();

    bool getInvert();
    int getSensitivity();
    void setInvert(bool doInvert);
    void setSensitivity(int sensitivity);

    void setXRange(int minX, int maxX);
    void setYRange(int minY, int maxY);
    void setRRange(int minR, int maxR);

    JoystickData read();
};
