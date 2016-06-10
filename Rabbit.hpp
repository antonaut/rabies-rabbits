#ifndef LAB3_RABBIT_HPP_
#define LAB3_RABBIT_HPP_

#include "Actor.hpp"
#include "EventBus.hpp"
#include "Environment.hpp"
#include "CharacterClass.hpp"
#include "CharacterRace.hpp"


namespace dnd {
class Rabbit : public Actor {
public:

Rabbit(EventBus *ebp,
           Environment *start_pos,
           DungeonMap *dm) : Actor(ebp,
                                  start_pos,
                                  dmap,
                                  RACE_RABBIT) {}



};

}  // namespace dnd


#endif  // LAB3_RABBIT_HPP_
