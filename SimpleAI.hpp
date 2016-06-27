// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include "Actor.hpp"
#include "Player.hpp"
#include "DungeonMap.hpp"

#ifndef LAB3_SIMPLEAI_HPP_
#define LAB3_SIMPLEAI_HPP_

namespace lab3 {

struct SimpleAI: virtual public Actor {
  int wimpyTurns = 0;

  SimpleAI(const Environment *position, DungeonMap *dm, const Race *race) : Actor(position, dm, race) { }

  virtual void fight(Actor *target) {
    if (this->isDead()) {
      std::clog << this->id << " is dead, so it can't fight." << std::endl;
      return;
    }
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

    if (this->tickHasChangedSinceLastAction() && tickCount % this->speed == 0) {
      Player *player = getPlayer();
      if (current_state == AGGRESSIVE) {
        if (current_health < max_health >> 2) {
          current_state = WIMPY;
          wimpyTurns = 0;
        }
        if (player->getPosition()->id == this->position->id) {
          this->fight(player);
          Actor::action();
          return;
        }

        Actor::moveTowards(player->getPosition());

        if (player->getPosition()->id == this->position->id) {
          auto noise = this->race->noise();
          std::cout << "[" << this->id << "] - A " << *this->race << " has arrived: " << noise <<
              std::endl;
        }
        Actor::action();
        return;

      } else if (current_state == WIMPY) {
        ++wimpyTurns;
        if (wimpyTurns >= 3) {
          this->current_state = NEUTRAL;
          wimpyTurns = 0;
        }
        if (closeToPlayer(player)) {
          std::cout << "[" << this->id << "] - A " << *this->race << " is fleeing." << std::endl;
        }
        this->flee();
        Actor::action();
        return;
      } else { // NEUTRAL

        if (closeToPlayer(player)) {
          this->current_state = AGGRESSIVE;
        }
        this->wait();
      }
    } else {
      wait();
    }
    Actor::action();
  }

  bool closeToPlayer(const Player *player) const {
    return game_map->bfs(position, player->getPosition(), game_map).size() <= 2;
  }
};

} // namespace lab3

#endif // LAB3_SIMPLEAI_HPP_
