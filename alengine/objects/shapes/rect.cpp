#include "rect.hpp"

namespace ae::object {
    Rect::Rect() {}
    Rect::Rect(const Material& mat)
        : mat(mat) {}
    Rect::Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size)
        : pos(pos), size(size), mat(mat) {}

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
