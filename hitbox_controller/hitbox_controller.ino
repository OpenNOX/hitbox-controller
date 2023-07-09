#include "button.h"

// number of milliseconds between animation frames
#define ANIMATION_THRESHOLD_MS 1500

// number of milliseconds to be considered idle
#define IDLE_THRESHOLD_MS 50000

// initialize buttons
Button upButton(22, 23, 0x61);
Button downButton(24, 25, 0x62);
Button leftButton(26, 27, 0x63);
Button rightButton(28, 29, 0x64);
Button bottomAction1Button(30, 31, 0x65);
Button bottomAction2Button(32, 33, 0x66);
Button bottomAction3Button(34, 35, 0x67);
Button bottomAction4Button(36, 37, 0x68);
Button topAction1Button(38, 39, 0x69);
Button topAction2Button(40, 41, 0x6A);
Button topAction3Button(42, 43, 0x6B);
Button topAction4Button(44, 45, 0x6C);
Button extraAction1Button(46, 47, 0x6D);
Button extraAction2Button(48, 49, 0x6E);
Button extraAction3Button(50, 51, 0x6F);

// initialize array of pointers to all buttons
Button *buttons[15] = {&upButton, &downButton, &leftButton, &rightButton, &bottomAction1Button, &bottomAction2Button, &bottomAction3Button, &bottomAction4Button, &topAction1Button, &topAction2Button, &topAction3Button, &topAction4Button, &extraAction1Button, &extraAction2Button, &extraAction3Button};

// initialize run environment
void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  randomSeed(analogRead(0));
}

// run main program loop
void loop()
{
  for (Button *button : buttons)
  {
    button->updateState();
  }

  inputLoop();

  if (isIdle())
  {
    idleLoop();
  }
}

// initialize last input tick
unsigned long lastInputTick = 0;

// has the idle threshold been reached?
bool isIdle()
{
  for (Button *button : buttons)
  {
    if (button->isPressed())
    {
      lastInputTick = millis();
      return false;
    }
  }

  return millis() - lastInputTick >= IDLE_THRESHOLD_MS;
}

// run input controller mode loop
void inputLoop()
{
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

// initialize last frame tick
unsigned long lastFrameTick = 0;

// run idle controller mode loop
void idleLoop()
{
  if (millis() - lastFrameTick <= ANIMATION_THRESHOLD_MS)
  {
    return;
  }

  lastFrameTick = millis();

  buttons[random(15)]->toggleLed();
}
