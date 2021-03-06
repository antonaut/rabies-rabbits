// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_ACTOR_HPP_
#define LAB3_ACTOR_HPP_

#include <cstdint>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>

#include "GameObject.hpp"
#include "Environment.hpp"
#include "Race.hpp"
#include "Item.hpp"

namespace lab3 {

std::mt19937 mt_engine;

class Actor;

std::vector<Actor *> ACTORS;

typedef int ActorSpeed;

const ActorSpeed SLOW(5);
const ActorSpeed NORMAL(3);
const ActorSpeed FAST(2);
const ActorSpeed PRETTY_DAMN_FAST(1);

typedef std::string ActorState;

ActorState AGGRESSIVE("Aggressive");
ActorState NEUTRAL("Neutral");
ActorState WIMPY("Wimpy");


class Actor: virtual public GameObject {
 public:

  uint32_t getCurrent_health() const {
    return this->current_health;
  }

  uint32_t getMax_health() const {
    return max_health;
  }

  const Environment *getPosition() const {
    return position;
  }

  uint64_t getPositionId() const {
    return position->id;
  }

  const Race *getRace() const {
    return race;
  }

  const bool isDead() const {
    return this->is_dead;
  }

  DungeonMap *getGame_map() const {
    return game_map;
  }

  void setCurrent_health(uint32_t current_health) {
    Actor::current_health = current_health;
  }

  void setPosition(const Environment *env) {
    Actor::position = env;
  }

 protected:
  uint32_t current_health;
  uint32_t max_health;
  uint32_t bonus_damage;
  bool bonus_applied;

  ActorSpeed speed;
  ActorState current_state = AGGRESSIVE;
  DungeonMap *game_map;
  const Race *race;

  bool is_dead;

  uint32_t base_damage;
  const Environment *position;
  int max_carry_capacity;

 public:
  Actor(const Environment *position,
        DungeonMap *game_map,
        const Race *race) :
      GameObject(),
      current_health(100),
      max_health(current_health),
      bonus_damage(0),
      bonus_applied(true),
      speed(NORMAL),
      game_map(game_map),
      race(race),
      is_dead(false),
      base_damage(10),
      position(position),
      max_carry_capacity(2000) {
    ACTORS.push_back(this);
  }

  virtual ~Actor() {

  }

  virtual void heal(uint32_t amount) {
    uint64_t sum = this->current_health + amount;
    if (sum >= this->max_health) {
      this->current_health = this->max_health;
    } else {
      this->current_health = (uint32_t) sum;
    }
  }

  virtual void hurt(uint32_t damage) {
    if (this->is_dead)
      return;
    int32_t diff = this->current_health - damage;

    for (auto ip : *getInventory(this->id)) {
      diff -= ip->getDefence();
    }

    if (diff <= 0) {
      this->die();
      this->current_health = 0;
      return;
    }

    this->current_health = (uint32_t) diff;
  }

  virtual void die() {
    this->howl();
    this->is_dead = true;
    std::clog << this->id << " just died." << std::endl;
    for (auto ip : *getInventory(this->id)) {
      this->drop(ip->id);
    }
  }

  virtual bool go(Direction dir) {
    const Environment *new_loc;
    try {
      new_loc = this->game_map->env_from_exit(this->position, dir);
    } catch (const std::invalid_argument &ex) {
      std::clog << ex.what();
      return false;
    }
    this->position = new_loc;
    return true;
  }

  virtual std::string noise() {
    return this->race->noise();
  }

  virtual void howl() {
    std::string n = this->noise();
    std::locale loc;
    for (std::size_t i = 0; i < n.length(); ++i) {
      std::cout << std::toupper(n[i], loc);
    }
    std::cout << std::endl;
    this->bonus_damage = 10;
    this->bonus_applied = false;
  }

  virtual uint32_t damage() {
    uint32_t total_damage = this->base_damage;

    if (!this->bonus_applied) {
      total_damage += this->bonus_damage;
      this->bonus_applied = true;
      this->bonus_damage = 0;
    }

    for (auto ip : *getInventory(this->id)) {
      total_damage += ip->getDamage();
    }

    return total_damage;
  }

  virtual void fight(Actor *target) { }

  virtual void action() {
    GameObject::action();
  }

  friend
  std::ostream &operator<<(std::ostream &str, const Actor &actor);

  void moveTowards(const Environment *target_location) {
    std::vector<Direction> path = this->game_map->bfs(Actor::position, target_location, Actor::game_map);
    if (path.empty()) { // already there
      return this->wait();
    }

    std::clog << Actor::id << " - move according to path ";
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
      std::clog << *it << " ";
    }
    std::clog << std::endl;

    this->go(*(--path.end()));
  }

  // Flee in a random direction
  void flee() {
    std::vector<Direction> exits = this->game_map->exits(this->position);

    std::uniform_int_distribution<int> distribution(0, (int) exits.size() - 1);

    int exit_index = distribution(mt_engine);

    this->go(exits[exit_index]);
  }

  virtual void wait() const {
    std::clog << Actor::id << " waits." << std::endl;
  }

  bool strongEnoughToCarry(Item *pItem) const;

  int carryCapacity() const;

  virtual int getMaxCarryCapacity() const;


  int totalCarryWeight() const;

  virtual bool drop(const uint64_t item_id) {
    bool transferred = item_transfer(item_id, this->id, this->getPositionId());
    if (transferred) {
      Item *item = findItemById(item_id);
      std::clog << item->getName() << " dropped by " << *this;
    }

    return transferred;
  }

  virtual bool take(const uint64_t item_id) {
    Item *item = findItemById(item_id);

    if (!this->strongEnoughToCarry(item)) {
      return false;
    }

    bool transferred = item_transfer(item_id, this->getPositionId(), this->id);
    if (transferred) {
      std::clog << item->getName() << " taken up by " << *this;
    }

    return transferred;
  }

};

std::ostream &operator<<(std::ostream &str, const Actor &actor) {
  str << *actor.race << " [" << actor.id << "] (" << actor.current_health << "/"
      << actor.max_health << ")" << " - " << actor.current_state;
  return str;
}

bool Actor::strongEnoughToCarry(Item *pItem) const{
  return pItem->getWeight() < this->carryCapacity();
}

int Actor::carryCapacity() const {
  return this->getMaxCarryCapacity() - this->totalCarryWeight();
}

int Actor::getMaxCarryCapacity() const {
  return this->max_carry_capacity;
}

int Actor::totalCarryWeight() const {
  int total_carry_weight(0);
  for (Item *ip: *getInventory(this->id)) {
    total_carry_weight += ip->getWeight();
  }
  return total_carry_weight;
}


std::vector<Actor *> findActorsByPosition(const Environment *position) {
  std::vector<Actor *> atPosition;
  for (auto &actor : ACTORS) {
    if (actor->getPosition() == position) {
      atPosition.push_back(actor);
    }
  }

  return atPosition;
}

std::vector<Actor *> findActorsByNameAtPosition(std::string name, const Environment *position) {
  std::vector<Actor *> found_actors;
  std::transform(name.begin(), name.end(), name.begin(), [](int c){ return std::tolower(c);});

  for (auto &actor : ACTORS) {
    if (actor->getPositionId() == position->id) {
      std::string race_name = actor->getRace()->name;
      std::transform(race_name.begin(), race_name.end(), race_name.begin(), [](int c){ return std::tolower(c);});
      if (!name.compare(race_name)) {
        found_actors.push_back(actor);
      }
    }
  }
  return found_actors; // OK to return a copy since there won't be that many in the same room.
}

}  // namespace lab3


#endif  // LAB3_ACTOR_HPP_
