#pragma once

#include "util/glm.hpp"

namespace ae::physics {
    class HitboxPoint;
    class HitboxAABB;
    class HitboxLine;
    class HitboxCircle;
    class Hitbox {
    public:
        virtual bool collide(const Hitbox& h) const =0;
        virtual bool collide(const HitboxPoint& h) const =0;
        virtual bool collide(const HitboxAABB& h) const =0;
        virtual bool collide(const HitboxLine& h) const =0;
        virtual bool collide(const HitboxCircle& h) const =0;
    };

    class HitboxPoint : Hitbox {
    public:
        glm::vec2 pos;

        HitboxPoint();
        HitboxPoint(const glm::vec2& pos);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    };

    class HitboxAABB : Hitbox {
    public:
        glm::vec2 pos;
        glm::vec2 size;

        HitboxAABB();
        HitboxAABB(const glm::vec2& pos, const glm::vec2& size);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    };

    class HitboxLine : Hitbox {
    public:
        glm::vec2 p1;
        glm::vec2 p2;

        HitboxLine();
        HitboxLine(const glm::vec2& p1, const glm::vec2& p2);

        float length() const;

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    };

    class HitboxCircle : Hitbox {
    public:
        glm::vec2 pos;
        float rad;

        HitboxCircle();
        HitboxCircle(const glm::vec2& pos, float rad);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    };
};
