#pragma once

#include "util/glm.hpp"

namespace ae {
    class HitboxPoint;
    class HitboxAABB;
    class HitboxLine;
    class HitboxCircle;
    class Hitbox {
    public:
        virtual bool collide(const Hitbox& h) const =0;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    };

    class HitboxPoint : Hitbox {
    public:
        glm::vec2& pos;

        HitboxPoint();
        HitboxPoint(const glm::vec2& pos);
        HitboxPoint(glm::vec2* pos);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    
    private:
        glm::vec2 pos_;
    };

    class HitboxAABB : Hitbox {
    public:
        glm::vec2& pos;
        glm::vec2& size;

        HitboxAABB();
        HitboxAABB(const glm::vec2& pos, const glm::vec2& size);
        HitboxAABB(glm::vec2* pos, glm::vec2* size);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    
    private:
        glm::vec2 pos_;
        glm::vec2 size_;
    };

    class HitboxLine : Hitbox {
    public:
        glm::vec2& p1;
        glm::vec2& p2;

        HitboxLine();
        HitboxLine(const glm::vec2& p1, const glm::vec2& p2);
        HitboxLine(glm::vec2* p1, glm::vec2* p2);

        float length() const;

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    
    private:
        glm::vec2 p1_;
        glm::vec2 p2_;
    };

    class HitboxCircle : Hitbox {
    public:
        glm::vec2& pos;
        float& rad;

        HitboxCircle();
        HitboxCircle(const glm::vec2& pos, float rad);
        HitboxCircle(glm::vec2* pos, float* rad);

        virtual bool collide(const Hitbox& h) const;
        virtual bool collide(const HitboxPoint& h) const;
        virtual bool collide(const HitboxAABB& h) const;
        virtual bool collide(const HitboxLine& h) const;
        virtual bool collide(const HitboxCircle& h) const;
    
    private:
        glm::vec2 pos_;
        float rad_;
    };
};
