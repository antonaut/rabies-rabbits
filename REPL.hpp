// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_REPL_HPP_
#define LAB3_REPL_HPP_

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "GameObject.hpp"
#include "Player.hpp"
#include "TickCount.hpp"

namespace lab3 {

typedef std::vector<std::string> Tokens;

struct Repl: public GameObject {
 private:
  void split(std::string str, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim)) {
      if (!item.empty()) {
        elems.push_back(item);
      }
    }
  }

  Player *player;
  SmallGameMap *smallGameMap;
  Tokens prev{""};
 public:
  Repl(Player *player, SmallGameMap *smallGameMap = nullptr)
      : GameObject(), player(player), smallGameMap(smallGameMap) { }

  virtual void action() {

    // Read -> Eval -> Print -> Loop => REPL

    std::cout << this->player->get_name() << " - "
        << this->player->getCurrent_health()
        << "/" << this->player->getMax_health() << ">";
    std::string command_input;
    std::getline(std::cin, command_input);

    if (std::cin.eof()) {
      throw std::out_of_range("Ctrl-D"); // Quit game
    }

    Tokens tokens;
    this->split(command_input, ' ', tokens);

    try {
      this->parse(tokens);
    } catch (std::invalid_argument &ex) {
      std::cout << "Arglebargle, glop-glyf!?!" << std::endl;
    }
  }


  void parse(Tokens &tokens) {
    if (tokens.empty()) return;
    this->previous(tokens);
  }

  inline void previous(Tokens &tokens) {
    if (*tokens.begin() == "p") {
      this->look(this->prev);
    } else {
      this->prev = tokens;
      this->look(tokens);
    }
  }


  inline void playerLook() {
    std::clog << "player look" << std::endl;
    std::cout << std::endl << player->getPosition()->name << std::endl;
    for (size_t i = 0; i < player->getPosition()->name.size(); i++) {
      std::cout << "=";
    }
    std::cout << std::endl << player->getPosition()->short_description << std::endl << std::endl;

    for (auto &actor : findActorsByPosition(player->getPosition())) {
      if (actor->id != player_id)
        std::cout << "[" << actor->id << "] - A " << *actor->getRace() << " is here." << std::endl;
    }

    if (!inventories[player->getPositionId()].empty()) {
      std::cout << std::endl << std::endl << "Items:" << std::endl;
    }
    for (auto &item : inventories[player->getPositionId()]) {
      std::cout << "[" << item->id << "] - " << item->getName();
    }

    this->printExits();
  }

  void printExits() const {
    std::cout << "Exits: ";
    std::vector<Direction> exits = player->getGame_map()->exits(player->getPosition());

    if (exits.size() > 1) {
      for (size_t i = 0; i < exits.size() - 1; ++i) {
        std::cout << exits[i] << ", ";
      }
    }
    std::cout << exits[exits.size() - 1];
    std::cout << std::endl;
  }

  inline void look(Tokens &tokens) {
    if (*tokens.begin() == "look") {
      this->playerLook();
      return;
    }
    this->inventory(tokens);
  }

  inline void inventory(Tokens &tokens) {
    if (*tokens.begin() == "inv" ||
        *tokens.begin() == "inventory") {
      return;
    }
    this->help(tokens);
  }


  inline void help(Tokens &tokens) {
    if (*tokens.begin() == "help" ||
        *tokens.begin() == "man") {

      std::cout << "There are a few commands:" << std::endl
          << "    help - prints this help." << std::endl
          << "    look - look around you." << std::endl
          << "    wait - wait a turn or two. Useful near glowing rocks." << std::endl
          << "    p - repeats the previous command entered." << std::endl
          << "    go *dir* - walk in direction: " << std::endl
          << "        *dir* can be any from " << std::endl
          << std::endl
          << "        \"north\", \"south\"" << std::endl
          << "        \"west\", \"east\"" << std::endl
          << "        \"up\", \"down\"" << std::endl
          << std::endl
          << "Interaction commands:"
          << std::endl
          << "    talk *target* - talks to *target*." <<
          std::endl
          << "    fight *target* - fights with *target*." <<
          std::endl
          << "    take *item* - takes *item*." << std::endl
          << "    inv - lists items in inventory." << std::endl
          << std::endl
          << "Type 'quit' to quit the game." << std::endl
          << std::endl
          << "Objects in the game are shown with their id."
          << std::endl
          << "Example:"
          << std::endl
          << "    [32] - Bird, where '32' is the id of the bird."
          << std::endl
          << std::endl
          << "In order to interact with the objects, simply use their id after the interaction."
          << std::endl
          << "Example:"
          << std::endl
          << "    '>fight 32'  -- fights with the bird"
          << std::endl
          << std::endl
          << "New commands may become available after you have gained some experience."
          << std::endl
          << std::endl;
      if (player->kills > 3) {
        std::cout << "   howl - gives you bonus damage for the next fight." << std::endl << std::endl;
      }
      return;
    }
    this->go(tokens);
  }


  inline void go(Tokens &tokens) {
    if (*tokens.begin() == "go" ||
        *tokens.begin() == "g") {
      auto it = ++tokens.begin();
      std::clog << "player go" << std::endl;
      bool moved;
      if (tokens.size() == 1) {
        std::cout << "Go in what direction?" << std::endl;
        return;
      }
      try {
        auto dir = parseDirection(*it);
        moved = this->player->go(dir);
      } catch (std::exception &ex) {
        moved = false;
      }

      if (moved) {
        this->playerLook();
        ++tickCount;
      } else {
        std::cout << "Unable to move in that direction." << std::endl;
      }

      return;
    }
    this->fight(tokens);
  }


  inline void fight(Tokens &tokens) {
    if (*tokens.begin() == "fight" ||
        *tokens.begin() == "kill" ||
        *tokens.begin() == "k") {

      if (tokens.size() < 2) {
        std::cout << "Fight who?" << std::endl;
        return;
      }

      auto it = ++tokens.begin();
      std::clog << "player fight " << *it << std::endl;
      uint64_t target_id = std::stoull(*it);
      GameObject *target;
      try {
        target = findGameObjectById(target_id);
      } catch (const std::invalid_argument &ex) {
        std::cout << "No such target found." << std::endl;
        return;
      }
      Actor *targetActor = dynamic_cast<Actor *>(target);
      if (targetActor->getPosition() == this->player->getPosition()) {
        this->player->fight(targetActor);
        ++tickCount;
        return;
      }
      std::cout << "No such target found." << std::endl;
      return;
    }
    this->talk(tokens);
  }


  inline void talk(Tokens &tokens) {
    if (*tokens.begin() == "talk") {
      auto it = ++tokens.begin();
      if (tokens.size() >= 2) {
        std::clog << "player talk " << *it << std::endl;
      }
      return;
    }
    this->take(tokens);
  }

  inline void take(Tokens &tokens) {
    if (*tokens.begin() == "take") {
      auto it = ++tokens.begin();
      if (tokens.size() >= 2) {
        std::clog << "player take " << *it << std::endl;
      }
      return;
    }
    this->wait(tokens);
  }

  inline void wait(Tokens &tokens) {
    if (*tokens.begin() == "wait") {

      std::clog << "player wait" << std::endl;

      uint32_t player_hp_diff = this->player->getMax_health() - this->player->getCurrent_health();

      if (this->player->getPosition()->id == this->player->start->id &&
          player_hp_diff > 0) {
        std::uint32_t health_amount = std::min((uint32_t) 20, player_hp_diff);
        this->player->heal(health_amount);
        std::cout << "The rock heals you with " << health_amount << " points." << std::endl;
      }
      ++tickCount;
      return;
    }
    this->quit(tokens);
  }

  inline void quit(Tokens &tokens) {
    if (*tokens.begin() == "quit") {
      throw std::out_of_range("Player quit.");
    }
    this->howl(tokens);
  }

  inline void howl(Tokens &tokens) {
    if (*tokens.begin() == "howl") {
      if (this->player->kills > 3) {
        player->howl();
        return;
      }
    }
    this->joke(tokens);
  }

  inline void joke(Tokens &tokens) {
    if (*tokens.begin() == "ls") {
      std::cout << "Did you mean 'rm -rf /'?" << std::endl;
      return;
    } else if (*tokens.begin() == "cd") {
      std::cout << "No such directory. Try 'go' instead." << std::endl;
      return;
    }
    this->teleport(tokens);
  }


  // Cheat, crashes the game if no argument is supplied on purpose
  inline void teleport(Tokens &tokens) {
    if (this->player->cls.name == character_classes[1].name) { // Only C++ programmer can teleport
      if (*tokens.begin() == "std::move") {
        if (*(tokens.begin() + 1) == "home") {
          player->teleport(player->start);
          playerLook();
          return;
        } else if (*(tokens.begin() + 1) == "mountain") {
          if (this->smallGameMap != nullptr) {
            player->teleport(this->smallGameMap->getBossSpawn());
            playerLook();
            return;
          }
        }
      }
    }
    throw std::invalid_argument("Argle.");
  }

};

}  // namespace lab3


#endif  // LAB3_REPL_HPP_
