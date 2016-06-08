// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include "GameObject.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "HealthComponent.hpp"
#include "EventBus.hpp"

namespace dnd {

struct Player : public GameObject {
    Player(EventBus *ebp,
           PlayerComponent *player_comp,
           HealthComponent *health_comp
           ):GameObject(ebp) {
        GameObject::add_component(player_comp);
        GameObject::add_component(health_comp);
    }

    void set_position(PositionComponent *pos_comp) {
        GameObject::add_component(pos_comp);
    }
};

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
