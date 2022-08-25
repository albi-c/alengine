#include "hitbox.hpp"

namespace ae {
    static const float TOLERANCE = 0.001f;

    bool Hitbox::collide(const HitboxPoint& h) const {
        return h.collide(*this);
    }
    bool Hitbox::collide(const HitboxAABB& h) const {
        return h.collide(*this);
    }
    bool Hitbox::collide(const HitboxLine& h) const {
        return h.collide(*this);
    }
    bool Hitbox::collide(const HitboxCircle& h) const {
        return h.collide(*this);
    }

    HitboxPoint::HitboxPoint()
        : pos(pos_) {}
    HitboxPoint::HitboxPoint(const glm::vec2& pos)
        : pos(pos_), pos_(pos) {}
    HitboxPoint::HitboxPoint(glm::vec2* pos)
        : pos(*pos) {}
    
    bool HitboxPoint::collide(const Hitbox& h) const {
        return h.collide(*this);
    }
    bool HitboxPoint::collide(const HitboxPoint& h) const {
        glm::vec2 a = glm::abs(pos - h.pos);
        return a.x < TOLERANCE && a.y < TOLERANCE;
    }
    bool HitboxPoint::collide(const HitboxAABB& h) const {
        return h.collide(*this);
    }
    bool HitboxPoint::collide(const HitboxLine& h) const {
        float ds = h.length();
        float l = glm::distance(h.p1, h.p2);
        return glm::abs(ds - l) < TOLERANCE;
    }
    bool HitboxPoint::collide(const HitboxCircle& h) const {
        return glm::distance(pos, h.pos) < h.rad;
    }

    HitboxAABB::HitboxAABB()
        : pos(pos_), size(size_) {}
    HitboxAABB::HitboxAABB(const glm::vec2& pos, const glm::vec2& size)
        : pos(pos_), size(size_), pos_(pos), size_(size) {}
    HitboxAABB::HitboxAABB(glm::vec2* pos, glm::vec2* size)
        : pos(*pos), size(*size) {}

    bool HitboxAABB::collide(const Hitbox& h) const {
        return h.collide(*this);
    }
    bool HitboxAABB::collide(const HitboxPoint& h) const {
        return h.pos.x > pos.x &&
               h.pos.y > pos.y &&
               h.pos.x < pos.x + size.x &&
               h.pos.y < pos.y + size.y;
    }
    bool HitboxAABB::collide(const HitboxAABB& h) const {
        return pos.x < h.pos.x + h.size.x &&
               pos.x + size.x > h.pos.x &&
               pos.y < h.pos.y + h.size.y &&
               pos.y + size.y > h.pos.y;
    }
    bool HitboxAABB::collide(const HitboxLine& h) const {
        return collide(HitboxPoint{h.p1}) || collide(HitboxPoint{h.p2}) ||
               h.collide(HitboxLine{pos, pos + glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos, pos + glm::vec2(0.0f, size.y)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(0.0f, size.y)});
    }
    bool HitboxAABB::collide(const HitboxCircle& h) const {
        glm::vec2 t = h.pos;

        if (h.pos.x < pos.x)          t.x = pos.x;
        if (h.pos.x > pos.x + size.x) t.x = pos.x + size.x;

        if (h.pos.y < pos.y)          t.y = pos.y;
        if (h.pos.y > pos.y + size.y) t.y = pos.y + size.y;

        glm::vec2 d_ = h.pos - t;
        float d = glm::length(d_);

        return d <= h.rad;
    }

    HitboxLine::HitboxLine()
        : p1(p1_), p2(p2_) {}
    HitboxLine::HitboxLine(const glm::vec2& p1, const glm::vec2& p2)
        : p1(p1_), p2(p2_), p1_(p1), p2_(p2) {}
    HitboxLine::HitboxLine(glm::vec2* p1, glm::vec2* p2)
        : p1(*p1), p2(*p2) {}
    
    float HitboxLine::length() const {
        return glm::distance(p1, p2);
    }
    
    bool HitboxLine::collide(const Hitbox& h) const {
        return h.collide(*this);
    }
    bool HitboxLine::collide(const HitboxPoint& h) const {
        return h.collide(*this);
    }
    bool HitboxLine::collide(const HitboxAABB& h) const {
        return h.collide(*this);
    }
    bool HitboxLine::collide(const HitboxLine& h) const {
        glm::vec2 s1 = p2 - p1;
        glm::vec2 s2 = h.p2 - h.p1;

        float s = (-s1.y * (p1.x - h.p1.x) + s1.x * (p1.y - h.p1.y)) / (-s2.x * s1.y + s1.x * s2.y);
        float t = ( s2.x * (p1.y - h.p1.y) - s2.y * (p1.x - h.p1.x)) / (-s2.x * s1.y + s1.x * s2.y);

        return s >= 0 && s <= 1 && t >= 0 && t <= 1;
    }
    bool HitboxLine::collide(const HitboxCircle& h) const {
        glm::vec2 d = p2 - p1;
        glm::vec2 f = p1 - h.pos;

        float a = glm::dot(d, d);
        float b = glm::dot(f, d) * 2.0f;
        float c = glm::dot(f, f) - h.rad * h.rad;

        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0.0f)
            return false;
        else {
            discriminant = glm::sqrt(discriminant);

            float t1 = (-b - discriminant) / (2.0f * a);
            float t2 = (-b + discriminant) / (2.0f * a);

            if (t1 >= 0 && t1 <= 1)
                return true;
            
            if (t2 >= 0 && t2 <= 1)
                return true;
        }

        return false;
    }
    
    HitboxCircle::HitboxCircle()
        : pos(pos_), rad(rad_) {}
    HitboxCircle::HitboxCircle(const glm::vec2& pos, float rad)
        : pos(pos_), rad(rad_), pos_(pos), rad_(rad) {}
    HitboxCircle::HitboxCircle(glm::vec2* pos, float* rad)
        : pos(*pos), rad(*rad) {}
    
    bool HitboxCircle::collide(const Hitbox& h) const {
        return h.collide(*this);
    }
    bool HitboxCircle::collide(const HitboxPoint& h) const {
        return h.collide(*this);
    }
    bool HitboxCircle::collide(const HitboxAABB& h) const {
        return h.collide(*this);
    }
    bool HitboxCircle::collide(const HitboxLine& h) const {
        return h.collide(*this);
    }
    bool HitboxCircle::collide(const HitboxCircle& h) const {
        return glm::distance(pos, h.pos) < rad + h.rad;
    }
};
