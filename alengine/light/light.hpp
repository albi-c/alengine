#pragma once

#include "util/glm.hpp"

namespace ae {
    struct Light {
        glm::vec2 pos;

        glm::vec3 color;
        float range;

        float angle = glm::radians(360.0f);
        float rotation = 0.0f;
    };
};
