// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <sstream>
#include "GameObject.hpp"
#include "Actor.hpp"
#include "CharacterRace.hpp"
#include "CharacterClass.hpp"
#include "DungeonMap.hpp"

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

        const CharacterClass &getCls() const {
            return cls;
        }

        std::string get_name() const {
            return name;
        }


        void fight(Actor *enemy) {
            uint32_t dmg = this->damage();
            enemy->hurt(dmg);

            std::stringstream ss;
            ss << enemy->race;

            this->cls.attack_fn(ss.str(), enemy->max_health, enemy->current_health, dmg);

            if (!enemy->is_dead) {
                std::cout << "The enemy hits you for " << enemy->base_damage << " points of damage." << std::endl;
                this->hurt(enemy->base_damage);
            }
        }

        virtual uint32_t damage() {
            return this->base_damage;
        }

        virtual void action() {

        }
    };


    Player *getPlayer() {
        return (Player *) findGameObjectById(player_id);
    }

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
