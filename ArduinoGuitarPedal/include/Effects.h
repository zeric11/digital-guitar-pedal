#ifndef ARDUINO_GUITAR_PEDAL_EFFECTS_H
#define ARDUINO_GUITAR_PEDAL_EFFECTS_H


#include <Arduino.h>
#include "U8glib.h"


#define INT16_MIN -32768
#define INT16_MAX 32767


class Effect {
protected:
    // Arduino int is 16-bit.
    // Max == 32767, Min == -32768.
    // Careful not to overflow int16.
    int modVal = 0;
    int modThresholdMin = 0;
    int modThresholdMax = 0;
    int modStep = 0;
    char name[16] = "NO EFFECT";

public:
    virtual void drawScreen(U8GLIB_SH1106_128X64& u8g); // { /* Do nothing by default */ };
    virtual void writeInput(int& input) { /* Do nothing by default */ }
    void handleModUpdate(int modDecrease, int modIncrease, int ledPin);
};


class BoostEffect: public Effect {
public:
    BoostEffect() {
        modVal = 10000;
        modThresholdMin = 0;
        modThresholdMax = 32767;
        modStep = 100;
        strcpy(name, "BOOST");
    }

    //void drawScreen(U8GLIB_SH1106_128X64& u8g) override;
    void writeInput(int& input) override;
};


class DistortionEffect: public Effect {
public:
    DistortionEffect() {
        modVal = 6000;
        modThresholdMin = 0;
        modThresholdMax = 32767;
        modStep = 100;
        strcpy(name, "DISTORTION");
    }

    //void drawScreen(U8GLIB_SH1106_128X64& u8g) override;
    void writeInput(int& input) override;
};


#endif // ARDUINO_GUITAR_PEDAL_EFFECTS_H