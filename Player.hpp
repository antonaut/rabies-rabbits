// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include "GameObject.hpp"
#include "Actor.hpp"
#include "CharacterRace.hpp"
#include "CharacterClass.hpp"

namespace dnd {

    uint64_t player_id;

    struct Player : public Actor {
    private:
        std::string name;
        CharacterClass cls;
    public:
        Player(const Environment *start,
               DungeonMap *dmap,
               std::string name,
               CharacterRace race,
               CharacterClass cls) : Actor(start,
                                           dmap,
                                           race),
                                     name(name),
                                     cls(cls) {
            player_id = Actor::id;
        }

        std::string get_name() const {
            return name;
        }


        void fight(Actor *enemy) {

        }

        virtual void action() {

        }
    };


    Player *getPlayer() {
        return (Player *) findGameObjectById(player_id);
    }

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
