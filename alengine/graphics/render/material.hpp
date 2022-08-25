#pragma once

#include "util/glm.hpp"
#include "graphics/texture/texture.hpp"

#include <memory>

namespace ae {
    struct Material {
        glm::vec3 color = glm::vec3(1.0f);
        std::shared_ptr<Texture> texture = nullptr;

        Material() {}
        Material(const glm::vec3& color)
            : color(color) {}
        Material(std::shared_ptr<Texture> texture)
            : texture(texture) {}
        Material(const glm::vec3& color, std::shared_ptr<Texture> texture)
            : color(color), texture(texture) {}
    };
};
