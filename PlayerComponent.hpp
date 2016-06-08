// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYERCOMPONENT_HPP_
#define LAB3_PLAYERCOMPONENT_HPP_

#include <vector>

#include "Component.hpp"
#include "EventBus.hpp"
#include "EnvironmentComponent.hpp"
#include "CharacterRace.hpp"
#include "CharacterClass.hpp"

namespace dnd {

    class PlayerComponent : public Component {
        private:
        std::string name;
        CharacterRace race;
        CharacterClass cls;

        public:
        PlayerComponent(std::string name,
                        CharacterRace &race,
                        CharacterClass &cls) :
            Component(ComponentType::PLAYER),
            name(name),
            race(race),
            cls(cls) {}
        std::string get_name() {
            return this->name;
        }
    };

}  // namespace dnd


#endif  // LAB3_PLAYERCOMPONENT_HPP_
