#include "line.hpp"

namespace ae::object {
    static constexpr float LINE_WIDTH = 1.0f;

    Line::Line()
        : HitboxLine() {}
    Line::Line(const Material& mat)
        : HitboxLine(), mat(mat) {}
    Line::Line(const Material& mat, const glm::vec2& p1, const glm::vec2& p2)
        : HitboxLine(p1, p2), mat(mat) {}
    Line::Line(const Material& mat, glm::vec2* p1, glm::vec2* p2)
        : HitboxLine(p1, p2), mat(mat) {}

    std::vector<Vertex> Line::vertices() const {
        return {
            {{p1, layer}, mat.color},
            {{p1 + LINE_WIDTH, layer}, mat.color},
            {{p2, layer}, mat.color},
            {{p2, layer}, mat.color},
            {{p2 + LINE_WIDTH, layer}, mat.color},
            {{p1, layer}, mat.color},
        };
    };
};
