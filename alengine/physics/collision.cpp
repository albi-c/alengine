#include "collision.hpp"

#include "engine.hpp"

namespace ae::physics {
    HitboxPoint::HitboxPoint() {}
    HitboxPoint::HitboxPoint(const glm::vec2& pos)
        : pos(pos) {}
    
    bool HitboxPoint::collide(const Hitbox& h) const {
        return h.collide(*this);
    }
    bool HitboxPoint::collide(const HitboxPoint& h) const {
        return pos == h.pos;
    }
    bool HitboxPoint::collide(const HitboxAABB& h) const {
        return h.collide(*this);
    }
    bool HitboxPoint::collide(const HitboxLine& h) const {
        float ds = h.length();
        float l = glm::distance(h.p1, h.p2);
        return ds == l;
    }
    bool HitboxPoint::collide(const HitboxCircle& h) const {
        return glm::distance(pos, h.pos) < h.rad;
    }

    HitboxAABB::HitboxAABB() {}
    HitboxAABB::HitboxAABB(const glm::vec2& pos, const glm::vec2& size)
        : pos(pos), size(size) {}

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
        return h.collide(HitboxLine{pos, pos + glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos, pos + glm::vec2(0.0f, size.y)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(0.0f, size.y)});
    }
    bool HitboxAABB::collide(const HitboxCircle& h) const {
        return h.collide(HitboxLine{pos, pos + glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos, pos + glm::vec2(0.0f, size.y)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(size.x, 0.0f)}) ||
               h.collide(HitboxLine{pos + size, pos - glm::vec2(0.0f, size.y)});
    }

    HitboxLine::HitboxLine() {}
    HitboxLine::HitboxLine(const glm::vec2& p1, const glm::vec2& p2)
        : p1(p1), p2(p2) {}
    
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
        if (HitboxPoint{p1}.collide(h) || HitboxPoint{p2}.collide(h))
            return true;
        
        float l = length();
        float d = glm::dot(h.pos - p1, p2 - p1) / glm::pow(l, 2.0f);
        glm::vec2 c = p1 + (d * (p2 - p1));

        if (!HitboxPoint{c}.collide(*this))
            return false;
        
        return d < h.rad;
    }
    
    HitboxCircle::HitboxCircle() {}
    HitboxCircle::HitboxCircle(const glm::vec2& pos, float rad)
        : pos(pos), rad(rad) {}
    
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
