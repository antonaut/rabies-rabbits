// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_REPL_HPP_
#define LAB3_REPL_HPP_

#include "GameObject.hpp"
#include "REPLComponent.hpp"
#include "EventBus.hpp"
#include "Player.hpp"

namespace dnd {

struct Repl : public GameObject {
    Repl(EventBus *ebp, const Player *player_ptr):GameObject(ebp) {
        GameObject::add_component(new REPLComponent(ebp, player_ptr));
    }
};

}  // namespace dnd


#endif  // LAB3_REPL_HPP_
