// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_CROCODILE_HPP_
#define LAB3_CROCODILE_HPP_

#include "Actor.hpp"
#include "Environment.hpp"
#include "CharacterClass.hpp"
#include "Race.hpp"
#include "DungeonMap.hpp"
#include "SimpleAI.hpp"

namespace lab3 {

struct Crocodile: virtual public SimpleAI {
  Crocodile(const Environment *start, DungeonMap *dm) : Actor(start, dm, &RACE_CROCODILE),
                                                        SimpleAI(start, dm, &RACE_CROCODILE) {
    this->base_damage = 20;
    this->max_health = 70;
    this->current_health = this->max_health;
  }

  virtual bool go(Direction dir) override {
    if (this->position->type == SWAMP_TYPE) {
      this->speed = PRETTY_DAMN_FAST;
    } else {
      this->speed = NORMAL;
    }
    return Actor::go(dir);
  }

};

}  // namespace lab3


#endif  // LAB3_CROCODILE_HPP_
