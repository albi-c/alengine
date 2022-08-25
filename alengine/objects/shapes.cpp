#include "shapes.hpp"

namespace ae {
    Rect::Rect(const Material& mat)
        : Shape(mat), HitboxAABB() {}
    Rect::Rect(const Material& mat, const glm::vec2& pos, const glm::vec2& size)
        : Shape(mat), HitboxAABB(pos, size) {}
    Rect::Rect(const Material& mat, glm::vec2* pos, glm::vec2* size)
        : Shape(mat), HitboxAABB(pos, size) {}
    
    Line::Line(const Material& mat)
        : Shape(mat), HitboxLine() {}
    Line::Line(const Material& mat, const glm::vec2& p1, const glm::vec2& p2)
        : Shape(mat), HitboxLine(p1, p2) {}
    Line::Line(const Material& mat, glm::vec2* p1, glm::vec2* p2)
        : Shape(mat), HitboxLine(p1, p2) {}
    
    Circle::Circle(const Material& mat)
        : Shape(mat), HitboxCircle() {}
    Circle::Circle(const Material& mat, const glm::vec2& pos, float rad)
        : Shape(mat), HitboxCircle(pos, rad) {}
    Circle::Circle(const Material& mat, glm::vec2* pos, float* rad)
        : Shape(mat), HitboxCircle(pos, rad) {}
};
