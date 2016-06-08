// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_GAMEOBJECT_HPP_
#define LAB3_GAMEOBJECT_HPP_

#include <vector>
#include <initializer_list>
#include <memory>
#include <stdexcept>

#include "Component.hpp"
#include "EventBus.hpp"
#include "Event.hpp"

namespace dnd {

class GameObject {
 private:
    std::vector<Component*> components;
    std::vector<GameObject*> children;
 protected:
    EventBus *ebp;
 public:
    static uint64_t id_counter;
    uint64_t id;
    GameObject *parent;

    // Default constructor constructs an empty GameObject
    explicit GameObject(EventBus* ebp) : components(0), children(0), ebp(ebp), id(++id_counter) {
        ebp->fire(&EVT_GameObjectSpawned);
    }

    GameObject(EventBus* ebp,
               std::initializer_list<Component*> components) :
        components(components),
        children(0),
        ebp(ebp),
        id(++id_counter) {
        ebp->fire(&EVT_GameObjectSpawned);
    }


    virtual ~GameObject() {
        this->ebp->fire(&EVT_GameObjectDestroyed);
        for (auto &comp_ptr : this->components) {
            delete comp_ptr;
        }
    }

    // No copy, no move
    GameObject(const GameObject &go) = delete;
    GameObject(GameObject &&go) = delete;
    GameObject& operator=(const GameObject &go) = delete;
    GameObject& operator=(GameObject &&go) = delete;


    void add_children(std::initializer_list<GameObject*> children) {
        this->children.insert(this->children.end(),
                              children.begin(),
                              children.end());
        for (auto &c : this->children) {
            c->setParent(this);
        };
    }

    void add_component(Component * cp) {
        this->components.push_back(cp);
    }

    void setParent(GameObject *parent) {
        this->parent = parent;
    }

    void fixed_update() {
        for (auto &c : this->components) {
            c->fixed_update();
        }
    }

    void update(double delta) {
        for (auto &c : this->components) {
            c->update(delta);
        }
    }

    Component* getComponent(ComponentType component_type) {
        for (auto &c : this->components) {
            if (c->get_type() == component_type) { return c; }
        }
        throw std::invalid_argument("No component with that ComponentType"
                                    " on this GameObject.");
    }
};

uint64_t GameObject::id_counter = 0;

}  // namespace dnd

#endif  // LAB3_GAMEOBJECT_HPP_
