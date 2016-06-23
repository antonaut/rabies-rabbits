// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_GAMEOBJECT_HPP_
#define LAB3_GAMEOBJECT_HPP_

#include <iostream>
#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <map>

#include "GameObject.hpp"

namespace lab3 {

    class GameObject;


    std::vector<GameObject *> GAME_OBJECTS;

    struct GameObject {
        static uint64_t id_counter;
        uint64_t id;

        // Default constructor constructs an empty GameObject
        explicit GameObject() : id(++id_counter) {
            GAME_OBJECTS.push_back(this);
        }


        virtual ~GameObject() { }

        // No copy, no move
        GameObject(const GameObject &go) = delete;

        GameObject(GameObject &&go) = delete;

        GameObject &operator=(const GameObject &go) = delete;

        GameObject &operator=(GameObject &&go) = delete;

        virtual void action() {

        }

        friend bool operator==(const GameObject &a, const GameObject &b);
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

    bool operator==(const GameObject &a, const GameObject &b) {
        return a.id == b.id;
    }

}  // namespace lab3

#endif  // LAB3_GAMEOBJECT_HPP_
