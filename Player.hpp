// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include "GameObject.hpp"
#include "Actor.hpp"
#include "EventBus.hpp"
#include "CharacterRace.hpp"
#include "CharacterClass.hpp"

namespace dnd {

    struct Player : public Actor {
        private:
        std::string name;
        CharacterClass cls;
        public:
        Player(EventBus *ebp,
               Environment *start,
               DungeonMap *dmap,
               std::string name,
               CharacterRace race,
               CharacterClass cls) : Actor(ebp,
                                           start,
                                           dmap,
                                           race),
                                     name(name),
                                     cls(cls) {} 

        std::string get_name() const {
            return name;
        }
    };

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
