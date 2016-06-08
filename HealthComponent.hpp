#ifndef LAB3_HEALTH_HPP_
#define LAB3_HEALTH_HPP_

#include <cstdint>

#include "Component.hpp"

namespace dnd {

    struct HealthComponent : public Component {
        const uint32_t max_health;
        uint32_t current_health;
        HealthComponent(int max_health) : Component(ComponentType::HEALTH),
                                          max_health(max_health),
                                          current_health(max_health) {}
    };

}  // namespace dnd


#endif  // LAB3_HEALTH_HPP_
