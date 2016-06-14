// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_ACTOR_HPP_
#define LAB3_ACTOR_HPP_

#include <cstdint>
#include <iostream>

#include "GameObject.hpp"
#include "Environment.hpp"
#include "CharacterRace.hpp"

namespace dnd {
    class Actor;

    std::vector<Actor *> ACTORS;

    class Actor : public GameObject {
    public:

        uint32_t current_health;
        uint32_t max_health;
        uint32_t base_damage;
        const Environment *position;
        DungeonMap *game_map;
        CharacterRace race;

        Actor(const Environment *position,
              DungeonMap *game_map,
              CharacterRace race) :
                GameObject(),
                current_health(100),
                max_health(current_health),
                base_damage(10),
                position(position),
                game_map(game_map),
                race(race) {
            ACTORS.push_back(this);
        }

        virtual ~Actor() {
            for (auto it = ACTORS.begin(); it != ACTORS.end(); ++it) {
                if (*it == this) {
                    ACTORS.erase(it);
                    return;
                }
            }
        }


        uint32_t getCurrent_health() const {
            return this->current_health;
        }


        virtual void heal(uint32_t amount) {
            uint64_t sum = this->current_health + amount;
            if (sum > this->max_health) {
                this->current_health = this->max_health;
            }
        }

        virtual void hurt(uint32_t damage) {
            int32_t diff = this->current_health - damage;

            if (diff <= 0) {
                this->die();
            }
            this->current_health = (uint32_t) diff;
        }

        virtual void die() {
            GameObject::is_dead = true;
        }

        bool go(Direction dir) {
            const Environment *new_loc;
            try {
                new_loc = this->game_map->env_from_exit(this->position, dir);
            } catch (const std::invalid_argument &ex) {
                std::clog << ex.what();
                return false;
            }
            this->position = new_loc;
            return true;
        }

        virtual void reply() const {
            std::cout << this->race.noise();
        }

        virtual void howl() const {
            std::string n = this->race.noise();
            std::locale loc;
            for (std::size_t i = 0; i < n.length(); ++i) {
                std::cout << std::toupper(n[i], loc);
            }
            std::cout << std::endl;
        }

        virtual void fight(Actor *target) {

        }


        virtual void action() = 0;
    };

    std::vector<Actor *> findActorsByPosition(const Environment *position) {
        std::vector<Actor *> atPosition;
        for (auto &actor : ACTORS) {
            if (actor->position == position) {
                atPosition.push_back(actor);
            }
        }

        return atPosition;
    }

}  // namespace dnd


#endif  // LAB3_ACTOR_HPP_
