#ifndef __INPUT_LOOP_H__
#define __INPUT_LOOP_H__

// run input controller mode loop
void inputLoop(Button *buttons)
{
    // clean vertical Simultaneous Opposing Cardinal Directions (SOCD)
    buttons[UP_BUTTON].processInput((buttons[UP_BUTTON].isPressed() && buttons[DOWN_BUTTON].isPressed()) || buttons[UP_BUTTON].isPressed());
    buttons[DOWN_BUTTON].processInput(!buttons[UP_BUTTON].isPressed() && buttons[DOWN_BUTTON].isPressed());

    // clean horizontal SOCD
    buttons[LEFT_BUTTON].processInput(buttons[LEFT_BUTTON].isPressed() && !buttons[RIGHT_BUTTON].isPressed());
    buttons[RIGHT_BUTTON].processInput(buttons[RIGHT_BUTTON].isPressed() && !buttons[LEFT_BUTTON].isPressed());

    // handle remaining button inputs
    for (int i = A_BUTTON; i <= EXTRA_3_BUTTON; i++)
    {
        buttons[i].processInput(buttons[i].isPressed());
    }
}

#endif
