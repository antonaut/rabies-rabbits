// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_GAMEOBJECT_HPP_
#define LAB3_GAMEOBJECT_HPP_

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "GameObject.hpp"

namespace dnd {

    class GameObject;

    std::vector<GameObject *> GAME_OBJECTS;

    class GameObject {
    private:
    protected:
        bool is_dead;
    public:
        static uint64_t id_counter;
        uint64_t id;

        // Default constructor constructs an empty GameObject
        explicit GameObject() : is_dead(false), id(++id_counter) {
            GAME_OBJECTS.push_back(this);
            std::clog << "GameObjectSpawned - id(" << this->id << ")." << std::endl;
        }


        virtual ~GameObject() {
            for (auto it = GAME_OBJECTS.begin(); it != GAME_OBJECTS.end(); ++it) {
                if (*it == this) {
                    GAME_OBJECTS.erase(it);
                    return;
                }
            }
        }

        // No copy, no move
        GameObject(const GameObject &go) = delete;

        GameObject(GameObject &&go) = delete;

        GameObject &operator=(const GameObject &go) = delete;

        GameObject &operator=(GameObject &&go) = delete;

        virtual void fixed_update() {

        }
    };

    uint64_t GameObject::id_counter = 0;


    GameObject *findGameObjectById(uint64_t needle) {
        for (size_t i = 0; i < GAME_OBJECTS.size(); ++i) {
            if (GAME_OBJECTS[i]->id == needle) {
                return GAME_OBJECTS[i];
            }
        }
        throw std::invalid_argument("No GameObject with that id found.");
    }

}  // namespace dnd

#endif  // LAB3_GAMEOBJECT_HPP_
