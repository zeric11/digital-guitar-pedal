#include "Effects.h"


void boostInput(int& input, int boostVal) {
    // the amplitude of the input signal is modified by boostVal
    input = map(input, -32768, +32768, -boostVal, +boostVal);
}


void distortInput(int& input, int distThreshold) {
    // the input signal is 16bits (values from -32768 to +32768
    // the value is clipped to the distThreshold value
    if(input > distThreshold) input = distThreshold;
    else if(input < -distThreshold) input = -distThreshold;
}

/* -------------------------------------------------------------------------- */

void Effect::drawScreen(U8GLIB_SH1106_128X64& u8g) {
    u8g.firstPage(); 
    do {
        u8g.setFont(u8g_font_helvR14r);
        u8g.drawStr( 0, 30, name);    
        u8g.setPrintPos(30, 64); 
        u8g.setFont(u8g_font_helvR18r); 
        u8g.print(modVal);
    } while(u8g.nextPage());
}


void Effect::handleModUpdate(int modDecrease, int modIncrease, int ledPin) {
    if(modDecrease) {
        if(modVal - modStep >= modThresholdMin) modVal -= modStep;
        digitalWrite(ledPin, LOW); // blinks the led
        //Serial.println(modVal);
    }
    if(modIncrease) {
        // Careful not to overflow int16
        if(modVal <= modThresholdMax - modStep) modVal += modStep;
        digitalWrite(ledPin, LOW); // blinks the led
        //Serial.println(modVal);
    }
}


void BoostEffect::writeInput(int& input) {
    boostInput(input, modVal);
}


void DistortionEffect::writeInput(int& input) {
    distortInput(input, modVal);
    //boostInput(input, INT16_MAX - modVal);
}