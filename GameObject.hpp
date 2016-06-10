// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_GAMEOBJECT_HPP_
#define LAB3_GAMEOBJECT_HPP_

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "EventBus.hpp"
#include "Event.hpp"

namespace dnd {



class GameObject {
 private:
 protected:
    bool is_dead;
    EventBus *ebp;
 public:
    static uint64_t id_counter;
    uint64_t id;
    GameObject *parent;

    // Default constructor constructs an empty GameObject
    explicit GameObject(EventBus* ebp) : is_dead(false), ebp(ebp), id(++id_counter) {
        std::clog << "GameObjectSpawned - id(" << this->id << ")." << std::endl;
    }


    virtual ~GameObject() {}

    // No copy, no move
    GameObject(const GameObject &go) = delete;
    GameObject(GameObject &&go) = delete;
    GameObject& operator=(const GameObject &go) = delete;
    GameObject& operator=(GameObject &&go) = delete;

    virtual void fixed_update() {
        
    }
};

std::vector<GameObject*> GAME_OBJECTS;

uint64_t GameObject::id_counter = 0;

}  // namespace dnd

#endif  // LAB3_GAMEOBJECT_HPP_
