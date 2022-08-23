#include "circle.hpp"

namespace ae::object {
    static constexpr int CIRCLE_STEP = 3;
    static constexpr int CIRCLE_VERTICES = 1080 / CIRCLE_STEP;
    static constexpr int CIRCLE_STEPS = 360 / CIRCLE_STEP;

    Circle::Circle()
        : HitboxCircle() {}
    Circle::Circle(const Material& mat)
        : HitboxCircle(), mat(mat) {}
    Circle::Circle(const Material& mat, const glm::vec2& pos, float rad)
        : HitboxCircle(pos, rad), mat(mat) {}
    Circle::Circle(const Material& mat, glm::vec2* pos, float* rad)
        : HitboxCircle(pos, rad), mat(mat) {}

    std::vector<Vertex> Circle::vertices() const {
        std::vector<Vertex> vertices;
        vertices.reserve(CIRCLE_VERTICES);
        for (int i = 0; i < CIRCLE_STEPS; i++) {
            float r1 = glm::radians((float)(i * CIRCLE_STEP));
            float r2 = glm::radians((float)(i * CIRCLE_STEP + CIRCLE_STEP));
            vertices.push_back({{pos, layer}, mat.color});
            vertices.push_back({{pos + glm::vec2(cos(r1), sin(r1)) * rad, layer}, mat.color});
            vertices.push_back({{pos + glm::vec2(cos(r2), sin(r2)) * rad, layer}, mat.color});
        }
        return vertices;
    };
};
