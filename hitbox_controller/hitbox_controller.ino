#include "button.h"
#include "constants.h"
#include "idle_loop.h"
#include "input_loop.h"

// initialize buttons

Button buttons[15] = {
    Button(UP_BUTTON_PIN, UP_LED_PIN, UP_KEY_CODE),
    Button(DOWN_BUTTON_PIN, DOWN_LED_PIN, DOWN_KEY_CODE),
    Button(LEFT_BUTTON_PIN, LEFT_LED_PIN, LEFT_KEY_CODE),
    Button(RIGHT_BUTTON_PIN, RIGHT_LED_PIN, RIGHT_KEY_CODE),
    Button(A_BUTTON_PIN, A_LED_PIN, A_KEY_CODE),
    Button(B_BUTTON_PIN, B_LED_PIN, B_KEY_CODE),
    Button(RB_BUTTON_PIN, RB_LED_PIN, RB_KEY_CODE),
    Button(RT_BUTTON_PIN, RT_LED_PIN, RT_KEY_CODE),
    Button(X_BUTTON_PIN, X_LED_PIN, X_KEY_CODE),
    Button(Y_BUTTON_PIN, Y_LED_PIN, Y_KEY_CODE),
    Button(LB_BUTTON_PIN, LB_LED_PIN, LB_KEY_CODE),
    Button(LT_BUTTON_PIN, LT_LED_PIN, LT_KEY_CODE),
    Button(EXTRA_1_BUTTON_PIN, EXTRA_1_LED_PIN, EXTRA_1_KEY_CODE),
    Button(EXTRA_2_BUTTON_PIN, EXTRA_2_LED_PIN, EXTRA_2_KEY_CODE),
    Button(EXTRA_3_BUTTON_PIN, EXTRA_3_LED_PIN, EXTRA_3_KEY_CODE)};

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
  for (int buttonIndex = 0; buttonIndex < 15; buttonIndex++)
  {
    buttons[buttonIndex].updateState();
  }

  inputLoop(buttons);

  if (isIdle())
  {
    idleLoop(buttons);
  }
}

// initialize last input tick
unsigned long lastInputTick = 0;

// has the idle threshold been reached?
bool isIdle()
{
  for (Button button : buttons)
  {
    if (button.isPressed())
    {
      lastInputTick = millis();
      return false;
    }
  }

  return millis() - lastInputTick >= IDLE_THRESHOLD_MS;
}
