#pragma once

#include "util/glm.hpp"

namespace ae {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    struct TexVertex {
        glm::vec3 position;
        glm::vec2 uv;
    };
};
