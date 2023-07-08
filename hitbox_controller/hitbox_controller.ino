#include "button.h"

// number of milliseconds between animation frames
#define ANIMATION_THRESHOLD_MS 1500

// number of milliseconds to be considered idle
#define IDLE_THRESHOLD_MS 50000

// controller modes used to separate logic
enum Modes { Idle, Input };

// initialize buttons
const Button upButton(22, 23, 0x61);
const Button downButton(24, 25, 0x62);
const Button leftButton(26, 27, 0x63);
const Button rightButton(28, 29, 0x64);
const Button bottomAction1Button(30, 31, 0x65);
const Button bottomAction2Button(32, 33, 0x66);
const Button bottomAction3Button(34, 35, 0x67);
const Button bottomAction4Button(36, 37, 0x68);
const Button topAction1Button(38, 39, 0x69);
const Button topAction2Button(40, 41, 0x6A);
const Button topAction3Button(42, 43, 0x6B);
const Button topAction4Button(44, 45, 0x6C);
const Button extraAction1Button(46, 47, 0x6D);
const Button extraAction2Button(48, 49, 0x6E);
const Button extraAction3Button(50, 51, 0x6F);

// initialize controller mode
Modes mode = Modes::Input;

// initialize run environment
void setup() {
  // setup serial communication
  Serial.begin(9600);

  // initialize the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // turn built-in LED off
  digitalWrite(LED_BUILTIN, LOW);
}

// run main program loop
void loop() {
  updateButtonStates();
  inputLoop();

  if (mode == Modes::Idle || isIdle()) {
    mode = Modes::Idle;
  }

  if (mode == Modes::Idle) {
    idleLoop();
  }
}

// initialize button states for loop
void updateButtonStates() {
  upButton.updateState();
  downButton.updateState();
  leftButton.updateState();
  rightButton.updateState();
  bottomAction1Button.updateState();
  bottomAction2Button.updateState();
  bottomAction3Button.updateState();
  bottomAction4Button.updateState();
  topAction1Button.updateState();
  topAction2Button.updateState();
  topAction3Button.updateState();
  topAction4Button.updateState();
  extraAction1Button.updateState();
  extraAction2Button.updateState();
  extraAction3Button.updateState();
}

// is any button being pressed?
bool isAnyButtonPressed() {
  return upButton.isPressed() || downButton.isPressed() || leftButton.isPressed() || rightButton.isPressed()
    || bottomAction1Button.isPressed() || bottomAction2Button.isPressed() || bottomAction3Button.isPressed() || bottomAction4Button.isPressed()
    || topAction1Button.isPressed() || topAction2Button.isPressed() || topAction3Button.isPressed() || topAction4Button.isPressed()
    || extraAction1Button.isPressed() || extraAction2Button.isPressed() || extraAction3Button.isPressed();
}

// initialize last input tick
unsigned long lastInputTick = 0;

// has the idle threshold been reached?
bool isIdle() {
  if (isAnyButtonPressed()) {
    lastInputTick = millis();
    return false;
  }

  return millis() - lastInputTick > IDLE_THRESHOLD_MS;
}

// run input controller mode loop
void inputLoop() {
  // clean vertical Simultaneous Opposing Cardinal Directions (SOCD)
  upButton.processInput((upButton.isPressed() && downButton.isPressed()) || upButton.isPressed());
  downButton.processInput(!upButton.isPressed() && downButton.isPressed());

  // clean horizontal SOCD
  leftButton.processInput(leftButton.isPressed() && !rightButton.isPressed());
  rightButton.processInput(rightButton.isPressed() && !leftButton.isPressed());

  bottomAction1Button.processInput(bottomAction1Button.isPressed());
  bottomAction2Button.processInput(bottomAction2Button.isPressed());
  bottomAction3Button.processInput(bottomAction3Button.isPressed());
  bottomAction4Button.processInput(bottomAction4Button.isPressed());
  topAction1Button.processInput(topAction1Button.isPressed());
  topAction2Button.processInput(topAction2Button.isPressed());
  topAction3Button.processInput(topAction3Button.isPressed());
  topAction4Button.processInput(topAction4Button.isPressed());
  extraAction1Button.processInput(extraAction1Button.isPressed());
  extraAction2Button.processInput(extraAction2Button.isPressed());
  extraAction3Button.processInput(extraAction3Button.isPressed());
}

// initialize array of pointers to all buttons
const Button* buttons[15] = {
  &upButton, &downButton, &leftButton, &rightButton,
  &bottomAction1Button, &bottomAction2Button, &bottomAction3Button, &bottomAction4Button,
  &topAction1Button, &topAction2Button, &topAction3Button, &topAction4Button,
  &extraAction1Button, &extraAction2Button, &extraAction3Button
};

// initialize last frame time tick
unsigned long lastFrameTime = 0;

// bool animationState[15] = { false };
bool animationState = false;

// run idle controller mode loop
void idleLoop() {
  if (millis() - lastFrameTime < ANIMATION_THRESHOLD_MS) {
    return;
  }

  lastFrameTime = millis();

  if (animationState) {
    upButton.ledOn();
    downButton.ledOn();
    leftButton.ledOn();
    rightButton.ledOn();
    bottomAction1Button.ledOn();
    bottomAction2Button.ledOn();
    bottomAction3Button.ledOn();
    bottomAction4Button.ledOn();
    topAction1Button.ledOn();
    topAction2Button.ledOn();
    topAction3Button.ledOn();
    topAction4Button.ledOn();
    extraAction1Button.ledOn();
    extraAction2Button.ledOn();
    extraAction3Button.ledOn();
  } else {
    upButton.ledOff();
    downButton.ledOff();
    leftButton.ledOff();
    rightButton.ledOff();
    bottomAction1Button.ledOff();
    bottomAction2Button.ledOff();
    bottomAction3Button.ledOff();
    bottomAction4Button.ledOff();
    topAction1Button.ledOff();
    topAction2Button.ledOff();
    topAction3Button.ledOff();
    topAction4Button.ledOff();
    extraAction1Button.ledOff();
    extraAction2Button.ledOff();
    extraAction3Button.ledOff();
  }
}
