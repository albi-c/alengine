#include "rect.hpp"

namespace ae::object {
    // Rect::Rect()
    //     : HitboxAABB(&pos, &size), pos(pos_), size(size_) {}
    // Rect::Rect(const Material& mat)
    //     : HitboxAABB(&pos_, &size_), mat(mat), pos(pos_), size(size_) {}
    // Rect::Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size)
    //     : HitboxAABB(&this->pos_, &this->size_), pos(pos_), size(size_), pos_(pos), size_(size), mat(mat) {}
    // Rect::Rect(const Material& mat, glm::vec2* pos, glm::vec2* size)
    //     : HitboxAABB(pos, size), pos(*pos), size(*size), mat(mat) {}

    Rect::Rect()
        : HitboxAABB() {}
    Rect::Rect(const Material& mat)
        : HitboxAABB(), mat(mat) {}
    Rect::Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size)
        : HitboxAABB(pos, size), mat(mat) {}
    Rect::Rect(const Material& mat, glm::vec2* pos, glm::vec2* size)
        : HitboxAABB(pos, size), mat(mat) {}

    std::vector<Vertex> Rect::vertices() const {
        return {
            {{pos.x, pos.y, layer}, mat.color},
            {{pos.x, pos.y + size.y, layer}, mat.color},
            {{pos.x + size.x, pos.y + size.y, layer}, mat.color},
            {{pos.x, pos.y, layer}, mat.color},
            {{pos.x + size.x, pos.y + size.y, layer}, mat.color},
            {{pos.x + size.x, pos.y, layer}, mat.color}
        };
    };
};
