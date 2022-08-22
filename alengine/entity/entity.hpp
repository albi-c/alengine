#pragma once

#include "util/glm.hpp"
#include "objects/object.hpp"

namespace ae::entity {
    class Entity : public Drawable {
    public:
        object::Object* object;

        inline Entity(object::Object& object)
            : object(&object) {}

        inline virtual std::vector<Vertex> vertices() const {
            return object->vertices();
        }

        inline void draw() const {
            Renderer::render(*object);
        }
    };
};
