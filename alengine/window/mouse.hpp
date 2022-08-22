#pragma once

#ifndef BETTER_ENUMS_MACRO_FILE
#define BETTER_ENUMS_MACRO_FILE "enum/enum_macros.h"
#endif
#include "enum/enum.h"

namespace ae {
    BETTER_ENUM(MouseButton, int,
        BUTTON_1 = 0,
        BUTTON_2 = 1,
        BUTTON_3 = 2,
        BUTTON_4 = 3,
        BUTTON_5 = 4,
        BUTTON_6 = 5,
        BUTTON_7 = 6,
        BUTTON_8 = 7,

        LEFT = BUTTON_1,
        RIGHT = BUTTON_2,
        MIDDLE = BUTTON_3
    );
};