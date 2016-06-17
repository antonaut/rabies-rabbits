// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include "Actor.hpp"
#include "Player.hpp"
#include "DungeonMap.hpp"

#ifndef LAB3_SIMPLEAI_HPP_
#define LAB3_SIMPLEAI_HPP_

namespace lab3 {

    struct SimpleAI : public Actor {
        int wimpyTurns = 0;

        SimpleAI(const Environment *position, DungeonMap *dm, const Race *race) : Actor(position, dm, race) { }

        virtual void fight(Actor *target) {
            try {
                Player *player = getPlayer();
                if (target == player) {
                    std::cout << *this->race << " attacks!" << std::endl;
                    player->fight(this);
                    return;
                }
            } catch (const std::invalid_argument &ex) {
                // No player found
            }

            this->hurt(target->damage());
            target->hurt(this->damage());
        }

        virtual void action() {
            std::clog << *this << std::endl;

            if (tickCount % this->speed == 0) {
                Player *player = getPlayer();
                if (currentState == aggr) {

                    if (player->position->id == Actor::position->id) {
                        this->fight(player);
                        return;
                    }

                    Actor::moveTowards(player->position);

                    if (player->position->id == Actor::position->id) {
                        auto noise = this->race->noise();
                        std::cout << "[" << this->id << "] - has arrived: " << noise << std::endl;
                    }
                    return;

                } else if (currentState == wimpy) {
                    ++wimpyTurns;
                    if (wimpyTurns >= 3) {
                        this->currentState = neutral;
                        wimpyTurns = 0;
                    }
                    this->flee();

                    return;
                } else { // neutral

                    if (this->game_map->bfs(this->position, player->position, this->game_map).size() <= 2) {
                        this->currentState = aggr;
                    }
                    this->wait();
                }
            } else {
                wait();
            }

            if (Actor::current_health < Actor::max_health >> 1) {
                currentState = wimpy;
            }
        }
    };

} // namespace lab3

#endif // LAB3_SIMPLEAI_HPP_
