// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <sstream>
#include "GameObject.hpp"
#include "Actor.hpp"
#include "Race.hpp"
#include "CharacterClass.hpp"
#include "DungeonMap.hpp"

namespace lab3 {

uint64_t player_id;

struct Player: public Actor {
 private:
  std::string name;
  CharacterClass cls;
  const Environment *start;
 public:
  Player(const Environment *start,
         DungeonMap *dmap,
         std::string name,
         const Race *race,
         CharacterClass cls) : Actor(start,
                                     dmap,
                                     race),
                               name(name),
                               cls(cls),
                               start(start) {
    player_id = Actor::id;
    kills = 0;
  }

  friend class Repl;

  const CharacterClass &getCls() const {
    return cls;
  }

  std::string get_name() const {
    return name;
  }


  virtual
  int getMaxCarryCapacity() override {
    return Actor::getMaxCarryCapacity() + this->kills * 10;
  }


  void fight(Actor *enemy) {
    uint32_t dmg = this->damage();
    enemy->hurt(dmg);

    std::stringstream ss;
    ss << *enemy->getRace();

    this->cls.attack_fn(ss.str(), enemy->getMax_health(), enemy->getCurrent_health(), dmg);

    if (!enemy->isDead()) {
      std::cout << "The enemy hits you for " << enemy->damage() << " points of damage." << std::endl;
      this->hurt(enemy->damage());
    } else {
      ++this->kills;
      if (this->kills == 4) {
        std::cout <<
            "You learned to 'howl'. If you do this, it will give you bonus damage next fighting round." <<
            std::endl;
      }
    }
  }

  virtual uint32_t damage() {
    return Actor::damage() + 7 * kills;
  }

  virtual void action() override { }

  virtual bool take(uint64_t item_id) override {
    bool taken = Actor::take(item_id);
    Item *item = findItemById(item_id);

    if (taken) {
      std::cout << "You picked up: " << item->getName() << std::endl;
    } else {
      if (!this->strongEnoughToCarry(item)) {
        std::cout << "You are not strong enough to carry: "
            << item->getName()
            << std::endl;
      } else {
        std::cout << "No such item here." << std::endl;
      }
    }

    return taken;
  }

  void teleport(const Environment *env) {

    std::cout << "YOU CHEATER!" << std::endl;

    this->position = env;
  }

  uint32_t kills;
};


Player *getPlayer() {
  return dynamic_cast<Player *>(findGameObjectById(player_id));
}

}  // namespace lab3


#endif  // LAB3_PLAYER_HPP_
