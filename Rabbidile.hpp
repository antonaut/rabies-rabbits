// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RABBIDILE_HPP
#define LAB3_RABBIDILE_HPP

#include "Rabbit.hpp"
#include "Crocodile.hpp"
#include "SmallGameMap.hpp"

namespace lab3 {

    // This class is a pun on duck typing.
    // Also a top class in a diamond inheritance.
    // It describes the final boss of this game.

    class Rabbidile : public Rabbit, public Crocodile {
        SmallGameMap *smallGameMap;
        const Environment *start;
    public:
        Rabbidile(const Environment *start, DungeonMap *dm, SmallGameMap *smallGameMap) : Actor(start, dm,
                                                                                                &RACE_RABBIDILE),
                                                                                          SimpleAI(start, dm,
                                                                                                   &RACE_RABBIDILE),
                                                                                          Rabbit(start, dm),
                                                                                          Crocodile(start, dm),
                                                                                          smallGameMap(smallGameMap),
                                                                                          start(start) {
            Actor::current_health = 150;
            Actor::max_health = 150;
            Actor::base_damage = 30;
            Actor::speed = PRETTY_DAMN_FAST;
            Actor::current_state = NEUTRAL;
        }

        // It walks like a Crocodile...
        virtual bool go(Direction dir) override {
            if (this->current_state == AGGRESSIVE) {
                return Crocodile::go(dir);
            }
            return false;
        }

        // ...But quacks like a Rabbit!
        virtual std::string noise() override {
            return Rabbit::noise();
        }


        virtual void action() override {
            Player *player = getPlayer();
            std::clog << *this << std::endl;

            if (this->current_state == NEUTRAL) {
                if (Actor::current_health < Actor::max_health) {
                    if (this->position == this->start) {
                        if (!this->is_dead) {
                            this->heal(10);
                            std::cout << *Actor::race << " regained strength by a mysterious force!" << std::endl;
                            std::clog << Actor::id << " heals." << std::endl;
                        }
                        this->wait();
                        return;
                    } else {
                        moveTowards(this->start);
                        std::clog << Actor::id << " moved towards starting location." << std::endl;
                    }
                    if (closeToPlayer(player)) {
                        if (player->current_health < player->max_health) {
                            this->current_state = AGGRESSIVE;
                        }
                    }
                }
            } else if (this->current_state == AGGRESSIVE) {
                if (closeToPlayer(player)) {
                    if (this->position->id == player->position->id) {
                        this->howl();
                        player->fight(this);
                        std::clog << Actor::id << " howls and fights." << std::endl;
                        return;
                    } else {
                        this->moveTowards(player->position);
                        std::clog << Actor::id << " chases the player." << std::endl;
                        return;
                    }
                }
            }

            this->current_state = NEUTRAL;
            this->wait();
        }

        virtual void die() {
            std::cout << std::endl << std::endl
            << "A path to the mountain top suddenly opens!" << std::endl << std::endl;
            smallGameMap->addFinalExit();
            Actor::die();
        }
    };


} // namespace lab3

#endif // LAB3_RABBIDILE_HPP
