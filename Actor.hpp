// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_ACTOR_HPP_
#define LAB3_ACTOR_HPP_

#include <cstdint>
#include <iostream>


#include "GameObject.hpp"
#include "Environment.hpp"
#include "EventBus.hpp"
#include "CharacterRace.hpp"

namespace dnd {

class Actor : public GameObject {
    public:

    uint32_t current_health;
    uint32_t max_health;
    Environment *position;
    DungeonMap *game_map;
    CharacterRace race;
    
    Actor(EventBus *ebp,
          Environment* position,
          DungeonMap *game_map,
          CharacterRace race) :
        GameObject(ebp),
        current_health(100),
        max_health(current_health),
        position(position),
        game_map(game_map),
        race(race)
    {}

    uint32_t get_health() {
        return this->current_health;
    }
                                                       
    void heal(uint32_t amount) {
        uint64_t sum = this->current_health + amount;
        if (sum > this->max_health) {
            this->current_health = this->max_health;
        }
    }

    void hurt(uint32_t damage) {
        int64_t diff = this->current_health - damage;
        
        if (diff <= 0) {
            this->die();
        }
        this->current_health = (uint64_t) diff;
    }

    void die() {
        GameObject::is_dead = true;
    }

    void go (Direction dir) {
        Environment *new_loc;
        try {
            new_loc = this->game_map->env_from_exit(this->position, dir);
        } catch (const std::invalid_argument& ex) {
            std::clog << ex.what();
        }
        this->position = new_loc;
    }

    void reply() {
        std::cout << this->race.noise();
    }
    
    void howl() {
        std::string n = this->race.noise();
        std::locale loc;
        for (auto i = 0; i < n.length(); ++i) {
            std:.cout << to_upper(n[i], loc);
        }
        std::cout << std::endl;
    }

    virtual void action() = 0;
};

}  // namespace dnd


#endif  // LAB3_ACTOR_HPP_
