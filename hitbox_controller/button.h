#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <Arduino.h>

class Button
{
private:
    inline static uint8_t _keyboardBuffer[8] = {0};
    inline static unsigned long _debounceDelayMs = 50;

    int _switchPin;
    int _ledPin;
    uint8_t _keyCode;
    bool _isPressed;
    bool _isLedOn;

public:
    // initialize Button
    Button(int switchPin, int ledPin, uint8_t keyCode);

    // update internal state to use across a loop
    void updateState();

    // check if Button is physically pressed
    bool isPressed();

    // toggle Button LED on / off
    void toggleLed();

    // turn Button LED off
    void ledOff();

    // turn Button LED on
    void ledOn();

    // process Button input
    void processInput(bool isPressed);
};

#endif
