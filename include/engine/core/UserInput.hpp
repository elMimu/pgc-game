#pragma once

#include "raylib.h"

#if defined(PLATFORM_ANDROID)
    #define USING_TOUCH_INPUT
#endif

namespace UserInput
{
    struct ClickState
    {
        bool pressed = false;
        bool held = false;
        bool released = false;
        Vector2 position = {0, 0};
    };

    class InputTracker
    {
    public:
        ClickState click;

        void Update()
        {
            click.pressed = false;
            click.released = false;

        #ifdef USING_TOUCH_INPUT
            bool isTouching = (GetTouchPointCount() > 0);
            Vector2 currentPos = isTouching ? GetTouchPosition(0) : click.position;

            if (isTouching && !click.held)
            {
                click.pressed = true;
                click.held = true;
                click.position = currentPos;
            }
            else if (!isTouching && click.held)
            {
                click.released = true;
                click.held = false;
            }
            else if (isTouching && click.held)
            {
                click.position = currentPos;
            }

        #else
            bool isMouseDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
            Vector2 currentPos = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                click.pressed = true;
                click.held = true;
                click.position = currentPos;
            }
            else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                click.released = true;
                click.held = false;
            }
            else if (isMouseDown)
            {
                click.position = currentPos;
            }
        #endif
        }

        const ClickState& GetClick() const { return click; }
    };
}
