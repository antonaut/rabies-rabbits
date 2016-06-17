// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RABBIT_HPP_
#define LAB3_RABBIT_HPP_

#include <random>
#include <set>
#include <deque>
#include "Actor.hpp"
#include "Environment.hpp"
#include "CharacterClass.hpp"
#include "Race.hpp"
#include "Direction.hpp"
#include "DungeonMap.hpp"
#include "SimpleAI.hpp"

namespace lab3 {

    class Rabbit : public SimpleAI {
    public:

        Rabbit(const Environment *start_pos,
               DungeonMap *dm) : SimpleAI(start_pos,
                                          dm,
                                          &RACE_RABBIT) {
            Actor::current_health = 20;
            Actor::max_health = 20;
        }

        virtual bool go(Direction dir) override {
            if (this->position->type == FOREST_TYPE || this->position->type == MOUNTAIN_TYPE) {
                this->speed = FAST;
            } else {
                this->speed = SLOW;
            }
            return SimpleAI::go(dir);
        }

    };


}  // namespace lab3


#endif  // LAB3_RABBIT_HPP_
