#include "light.hpp"

#include "graphics/render/renderer.hpp"

namespace ae {
    void Light::draw(const glm::vec2& translate) {
        Renderer::render(*this, translate);
    }
};
