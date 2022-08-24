#pragma once

#include "shape.hpp"
#include "physics/collision.hpp"
#include "graphics/texture/texture.hpp"

namespace ae::object {
    class Sprite : public Shape, public physics::HitboxAABB {
    public:
        const Texture* tex;

        Sprite();
        Sprite(const Texture* tex);
        Sprite(const Texture* tex, const glm::vec2& pos, const glm::vec2& size);
        Sprite(const Texture* tex, glm::vec2* pos, glm::vec2* size);

        virtual std::vector<TexVertex> vertices_tex() const;
        virtual const Texture* texture() const;
    };
};
