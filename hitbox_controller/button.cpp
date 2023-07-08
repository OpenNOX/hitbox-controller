#include "button.h"

Button::Button(int switchPin, int ledPin, uint8_t keyCode)
{
    _switchPin = switchPin;
    _ledPin = ledPin;
    _keyCode = keyCode;

    pinMode(switchPin, INPUT);
    pinMode(ledPin, OUTPUT);

    updateState();
}

void Button::updateState() {
  _isPressed = digitalRead(_switchPin) == HIGH;
}

bool Button::isPressed() {
  return _isPressed;
}

void Button::ledOff() {
  digitalWrite(_ledPin, LOW);
}

void Button::ledOn() {
  digitalWrite(_ledPin, HIGH);
}

void Button::processInput(bool isPushed) {
  if (isPushed)
  {
    ledOn();

    // send keyboard input
    _keyboardBuffer[2] = _keyCode;
    Serial.write(_keyboardBuffer, 8);

    // end keyboard buffer data stream
    _keyboardBuffer[2] = 0;
    Serial.write(_keyboardBuffer, 8);
  }
  else
  {
    ledOff();
  }
}
