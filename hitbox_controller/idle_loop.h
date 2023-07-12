#ifndef __IDLE_LOOP_H__
#define __IDLE_LOOP_H__

#include "button.h"
#include "constants.h"

// initialize last frame tick
unsigned long lastFrameTick = 0;

// run idle controller mode loop
void idleLoop(Button *buttons)
{
    if (millis() - lastFrameTick <= ANIMATION_THRESHOLD_MS)
    {
        return;
    }

    lastFrameTick = millis();

    buttons[random(15)].toggleLed();
}

#endif
