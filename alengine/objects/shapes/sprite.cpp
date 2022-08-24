#include "sprite.hpp"

namespace ae::object {
    Sprite::Sprite(const Texture* tex)
        : HitboxAABB(), tex(tex) {}
    Sprite::Sprite(const Texture* tex, const glm::vec2& pos, const glm::vec2& size)
        : HitboxAABB(pos, size), tex(tex) {}
    Sprite::Sprite(const Texture* tex, glm::vec2* pos, glm::vec2* size)
        : HitboxAABB(pos, size), tex(tex) {}
    
    std::vector<TexVertex> Sprite::vertices_tex() const {
        return {
            {{pos.x, pos.y, layer}, {0.0f, 0.0f}},
            {{pos.x, pos.y + size.y, layer}, {0.0f, 1.0f}},
            {{pos.x + size.x, pos.y + size.y, layer}, {1.0f, 1.0f}},
            {{pos.x, pos.y, layer}, {0.0f, 0.0f}},
            {{pos.x + size.x, pos.y + size.y, layer}, {1.0f, 1.0f}},
            {{pos.x + size.x, pos.y, layer}, {1.0f, 0.0f}}
        };
    }
    const Texture* Sprite::texture() const {
        return tex;
    }
};
