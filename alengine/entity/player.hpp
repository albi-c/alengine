#pragma once

#include "entity.hpp"

namespace ae::entity {
    class Player : public Entity {
    public:
        Player(object::Object& object);
    };
};
