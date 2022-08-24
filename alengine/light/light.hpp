#pragma once

#include "util/glm.hpp"

namespace ae {
    struct Light {
        glm::vec2 pos;
        float range;

        glm::vec3 color;

        Light(const glm::vec2& pos, float range, const glm::vec3& color = glm::vec3(1.0f))
            : pos(pos), range(range), color(color) {}
        
        void draw(const glm::vec2& translate = glm::vec2(0.0f));
    };
};
