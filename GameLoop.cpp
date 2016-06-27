// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "GameObject.hpp"
#include "SmallGameMap.hpp"
#include "REPL.hpp"
#include "Intro.hpp"
#include "Rabbit.hpp"
#include "Crocodile.hpp"
#include "Rabbidile.hpp"

namespace lab3 {

bool handleDeath();

bool hasWon(SmallGameMap *sm);

void handleItemDecay();

void start_game_loop(SmallGameMap *sm) {
  bool quit(false);
  while (!quit) {
    int lastTick = tickCount;
    std::clog << "*** Tick: " << tickCount << " ***" << std::endl;
    for (auto &game_obj : GAME_OBJECTS) {
      try {
        game_obj->action();
      } catch (const std::out_of_range &ex) {
        quit = true;
        break;
      }
    }

    handleItemDecay();

    quit |= handleDeath();
    quit |= hasWon(sm);

    // Spawn more enemies
    if (tickCount > lastTick) {
      if (tickCount % 15 == 0) new Rabbit(sm->getRabbitSpawnTwo(), sm->getDungeonMap());
      if (tickCount % 25 == 0) new Crocodile(sm->getCrocSpawnTwo(), sm->getDungeonMap());
    }
  }
}

void deleteVoidInventory();

void handleItemDecay() {
  for (Item *itemPointer: ITEMS) {
    if (itemPointer->isDecayed()) {
      moveToVoid(itemPointer->id);
    }
  }

  deleteVoidInventory();
}

void deleteVoidInventory() {
  std::vector<Item *> *voidInventoryPointer = inventory(theVoid->id);

  std::vector<Item *> to_be_deleted;

  for (auto it = voidInventoryPointer->begin(); it != voidInventoryPointer->end(); ++it) {
    auto i = *it;

    auto gob_it = find(GAME_OBJECTS.begin(), GAME_OBJECTS.end(), i);
    if (gob_it != GAME_OBJECTS.end()) {
      GAME_OBJECTS.erase(gob_it);
    }

    auto item_it = find(ITEMS.begin(), ITEMS.end(), i);

    if (item_it != ITEMS.end()) {
      ITEMS.erase(item_it);
    }

    to_be_deleted.push_back(*it);
  }

  for (auto itemPointer : to_be_deleted) {
    delete itemPointer;
  }
  voidInventoryPointer->clear();
}

bool hasWon(SmallGameMap *sm) {
  Player *player = getPlayer();
  bool has_won = player->getPosition()->id == sm->getWinLocation()->id;

  if (has_won) {
    std::cout << "Congratulations! You have won the game! Please play again." << std::endl;
  }

  return has_won;
}

bool handleDeath() {
  bool quit = false;

  // Death
  std::vector<Actor *> dead_actors;
  for (std::vector<Actor *>::iterator it = ACTORS.begin(); it != ACTORS.end(); ++it) {
    if ((*it)->isDead()) {
      Actor *dead_actor = *it;
      Player *player = getPlayer();
      if (dead_actor->id == player->id) {
        quit = true;
        std::cout << "Oh dear, you are dead. Please play again!" << std::endl;
        break;
      }
      std::stringstream ss;
      ss << *dead_actor->getRace();
      player->getCls().killed_fn(ss.str());


      dead_actors.push_back(*it);
    }
  }

  // Memory management
  for (auto ap : dead_actors) {
    auto it = find(ACTORS.begin(), ACTORS.end(), ap);
    ACTORS.erase(it);
    auto it2 = find(GAME_OBJECTS.begin(), GAME_OBJECTS.end(), ap);
    GAME_OBJECTS.erase(it2);
    delete ap;
  }

  return quit;
}

}  // namespace lab3

using namespace lab3;

int main(int argc, char *argv[]) {

  SmallGameMap *sm = new SmallGameMap();

  Intro *intro = new Intro();

  Player *player;

  try {
    player = intro->create_player(sm->getStart(), sm->getDungeonMap());

    std::clog << "Player created: " << *player << std::endl;

    new Repl(player, sm);

    // Spawn actors, deleted upon death / exit
    new Rabbit(sm->getRabbitSpawnOne(),
               sm->getDungeonMap());
    new Rabbit(sm->getRabbitSpawnTwo(),
               sm->getDungeonMap());

    new Crocodile(sm->getCrocSpawnOne(),
                  sm->getDungeonMap());
    new Crocodile(sm->getCrocSpawnTwo(),
                  sm->getDungeonMap());

    new Rabbidile(sm->getBossSpawn(), sm->getDungeonMap(), sm);


    start_game_loop(sm);

  } catch (const std::out_of_range &oor) {
    std::cout << "Quit: " << oor.what() << std::endl;
  }

  // Memory management - cleanup

  for (auto ip : ITEMS) {
    moveToVoid(ip->id);
  }

  deleteVoidInventory();

  for (size_t i = 0; i < GAME_OBJECTS.size(); ++i) {
    delete GAME_OBJECTS[i];
  }

  ITEMS.clear();
  ACTORS.clear();
  GAME_OBJECTS.clear();

  return EXIT_SUCCESS;
}
