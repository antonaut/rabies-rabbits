#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <cstdint>

#include "Component.hpp"
#include "HealthComponent.hpp"
#include "GameObject.hpp"
#include "EventBus.hpp"
#include "Event.hpp"

namespace dnd {

    class Health : public GameObject {
        Health(EventBus *ebp) : GameObject(ebp) {}

        void heal(uint32_t amount) {
            HealthComponent *hc = (HealthComponent *) this->getComponent(ComponentType::HEALTH);

            uint64_t sum = hc->current_health + amount;
            if (sum > hc->max_health) {
                hc->current_health = hc->max_health;
            }
        }

        void hurt(uint32_t damage) {
            HealthComponent *hc = (HealthComponent *) this->getComponent(ComponentType::HEALTH);

            int64_t diff = hc->current_health - damage;
            if (diff <= 0) {
                this->die();
            }
            hc->current_health = (uint64_t) diff;
        }

        void die() {
            struct {
                uint64_t id;
            } die_evt_data;

            Event dead_evt("DEATH", (void*) &die_evt_data);
            GameObject::ebp->fire(&dead_evt);
        }

    };

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
