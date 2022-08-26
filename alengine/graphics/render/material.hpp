#pragma once

#include "util/glm.hpp"
#include "graphics/texture/texture.hpp"

#include <memory>

namespace ae {
    struct Material {
        glm::vec3 color = glm::vec3(1.0f);
        std::shared_ptr<Texture> texture = nullptr;
        glm::vec2 texture_repeat = glm::vec2(1.0f);

        Material() {}
        Material(const glm::vec3& color)
            : color(color) {}
        Material(std::shared_ptr<Texture> texture, glm::vec2 texture_repeat = glm::vec2(1.0f))
            : texture(texture), texture_repeat(texture_repeat) {}
        Material(const glm::vec3& color, std::shared_ptr<Texture> texture, glm::vec2 texture_repeat = glm::vec2(1.0f))
            : color(color), texture(texture), texture_repeat(texture_repeat) {}
    };
};
