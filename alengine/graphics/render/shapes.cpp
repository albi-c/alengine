#include "shapes.hpp"

namespace ae {
    RendererRect::RendererRect(const Rect& rect)
        : RendererShape(rect.mat), pos(rect.pos), size(rect.size) {}
    
    RendererLine::RendererLine(const Line& line)
        : RendererShape(line.mat), p1(line.p1), p2(line.p2) {}
    
    RendererCircle::RendererCircle(const Circle& circle)
        : RendererShape(circle.mat), pos(circle.pos), rad(circle.rad) {}
};
