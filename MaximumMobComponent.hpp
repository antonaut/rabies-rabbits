// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_MAXIMUMMOBCOMPONENT_HPP_
#define LAB3_MAXIMUMMOBCOMPONENT_HPP_

#include "Component.hpp"

namespace dnd {

class MaximumMobComponent : public Component {
    MaximumMobComponent() = delete;
    int max_mobs;
public:
    MaximumMobComponent(int max_mobs) : Component(ComponentType::MAXIMUM_MOB), max_mobs(max_mobs) {}
    virtual ~MaximumMobComponent() {}

    MaximumMobComponent(const MaximumMobComponent& mmc) : Component(ComponentType::MAXIMUM_MOB) {
        this->max_mobs = mmc.max_mobs;
    }

    MaximumMobComponent& operator=(const MaximumMobComponent& mmc) {
        this->max_mobs = mmc.max_mobs;
        return *this;
    }

};


}  // namespace dnd

#endif  // LAB3_MAXIMUMMOBCOMPONENT_HPP_
