// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RABBIDILE_HPP
#define LAB3_RABBIDILE_HPP

#include "Rabbit.hpp"
#include "Crocodile.hpp"

namespace lab3 {

    class Rabbidile : public Rabbit, public Crocodile {
    public:
        Rabbidile(const Environment *start, DungeonMap *dm) : Rabbit(start, dm), Crocodile(start, dm) {
            Actor::current_health = 150;
            Actor::max_health = 150;
            Actor::base_damage = 30;
            Actor::speed = PRETTY_DAMN_FAST;
            Actor::current_state = NEUTRAL;
        }

        virtual bool go(Direction dir) override {
            if (this->current_state == AGGRESSIVE) {
                return Crocodile::go(dir);
            }
        }

        virtual void action() override {
            if (Actor::current_health < Actor::max_health) {

                // Go into rage
                if (this->current_state == NEUTRAL) this->howl();
                this->current_state = AGGRESSIVE;
            }
        }
    };


} // namespace lab3

#endif // LAB3_RABBIDILE_HPP
