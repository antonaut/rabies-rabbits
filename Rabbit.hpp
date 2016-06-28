// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RABBIT_HPP_
#define LAB3_RABBIT_HPP_

#include <random>
#include <set>
#include <deque>
#include "Actor.hpp"
#include "Environment.hpp"
#include "CharacterClass.hpp"
#include "Race.hpp"
#include "Direction.hpp"
#include "DungeonMap.hpp"
#include "SimpleAI.hpp"
#include "RabbitPaw.hpp"

namespace lab3 {

class Rabbit: virtual public SimpleAI {
 public:

  Rabbit(const Environment *start_pos,
         DungeonMap *dm) : Actor(start_pos, dm, &RACE_RABBIT),
                           SimpleAI(start_pos,
                                    dm,
                                    &RACE_RABBIT) {
    Actor::current_health = 20;
    Actor::max_health = 20;

    std::uniform_int_distribution<int> distribution(0, 100);
    int d100 = distribution(mt_engine);

    if (d100 < 75) {
      new RabbitPaw(this->id);
    }
    d100 = distribution(mt_engine);
    if (d100 < 10) {
      Item *stick = new Item("stick", this->id, 2000, 30, 10, true);
      stick->setTicksUntilDecay(100);
    }
  }

  virtual bool go(Direction dir) override {
    if (this->position->type == FOREST_TYPE || this->position->type == MOUNTAIN_TYPE) {
      this->speed = FAST;
    } else {
      this->speed = SLOW;
    }
    return SimpleAI::go(dir);
  }

  virtual std::string noise() {
    std::stringstream ss;
    ss << this->race->noise();
    ss << " " << this->race->noise();
    return ss.str();
  }

};

}  // namespace lab3


#endif  // LAB3_RABBIT_HPP_
