#ifndef LAB3_RABBIT_HPP_
#define LAB3_RABBIT_HPP_

#include <random>
#include <set>
#include <deque>
#include "Actor.hpp"
#include "Environment.hpp"
#include "Player.hpp"
#include "CharacterClass.hpp"
#include "CharacterRace.hpp"
#include "Direction.hpp"
#include "DungeonMap.hpp"
#include "TickCount.hpp"


namespace dnd {

    typedef std::string rabbit_state;
    rabbit_state aggr("Aggressive");
    rabbit_state wimpy("Wimpy");

    class Rabbit : public Actor {
        const Environment *starting_pos;
        rabbit_state currentState = aggr;
    public:

        Rabbit(const Environment *start_pos,
               DungeonMap *dm) : Actor(start_pos,
                                       dm,
                                       RACE_RABBIT), starting_pos(start_pos) {
            Actor::current_health = 20;
            Actor::max_health = 20;
        }

        friend
        std::ostream& operator<<(std::ostream &str, const Rabbit &rabbit);

        virtual void action() {
            std::clog << *this << std::endl;

            if (tickCount % 3 == 0) {
                if (currentState == aggr) {
                    Player *player = getPlayer();
                    if (*player->position == *Actor::position) {
                        Actor::fight(player);
                        return;
                    }
                    Actor::moveTowards(player->position);
                    return;
                } else {
                    Actor::flee();
                    return;
                }
            } else {
                wait();
            }

            if (Actor::current_health < Actor::max_health >> 1) {
                currentState = wimpy;
            }

        }

    };

    std::ostream& operator<<(std::ostream &str, const Rabbit &rabbit) {
        const Actor * ap = &rabbit;
        str << *ap;
        str << " " << rabbit.currentState;
        return str;
    }


}  // namespace dnd


#endif  // LAB3_RABBIT_HPP_
