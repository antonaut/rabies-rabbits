#ifndef LAB3_CROCODILE_HPP_
#define LAB3_CROCODILE_HPP_

#include "Actor.hpp"
#include "Environment.hpp"
#include "CharacterClass.hpp"
#include "CharacterRace.hpp"
#include "DungeonMap.hpp"

namespace dnd {

    class Crocodile : public Actor {
    public:
        Crocodile(const Environment *start, DungeonMap *dm) : Actor(start, dm, RACE_CROCODILE) {
            this->base_damage = 20;
            this->max_health = 150;
            this->current_health = this->max_health;
        }
    };

}  // namespace dnd


#endif  // LAB3_CROCODILE_HPP_
