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

namespace lab3 {

    void start_game_loop() {
        bool quit(false);
        while (!quit) {
            std::clog << "*** Tick: " << tickCount << " ***" << std::endl;
            for (auto &game_obj : GAME_OBJECTS) {
                try {
                    game_obj->action();
                } catch (const std::out_of_range &ex) {
                    quit = true;
                    break;
                }
            }


            // Death
            std::vector<Actor *> dead_actors;
            for (std::vector<Actor *>::iterator it = ACTORS.begin(); it != ACTORS.end(); ++it) {
                if ((*it)->is_dead) {
                    Actor *dead_actor = *it;
                    Player *player = getPlayer();
                    if (dead_actor->id == player->id) {
                        quit = true;
                        std::cout << "Oh dear, you are dead. Please play again!" << std::endl;
                        break;
                    }
                    std::stringstream ss;
                    ss << *dead_actor->race;
                    player->getCls().killed_fn(ss.str());

                    dead_actors.push_back(*it);
                }
            }

            // Memory management
            for (auto ap : dead_actors) {
                auto it = std::find(ACTORS.begin(), ACTORS.end(), ap);
                ACTORS.erase(it);
                auto it2 = std::find(GAME_OBJECTS.begin(), GAME_OBJECTS.end(), ap);
                GAME_OBJECTS.erase(it2);
                delete ap;
            }

        }
    }

}  // namespace lab3

using namespace lab3;

int main(int argc, char *argv[]) {

    SmallGameMap *sm = new SmallGameMap();

    Intro *intro = new Intro();

    Player *player;

    try {
        player = intro->create_player(sm->getStart(), sm->getDungeonMap());

        new Repl(player);

        // Spawn actors, deleted upon death / exit
        new Rabbit(sm->getRabbitSpawnOne(),
                   sm->getDungeonMap());
        new Rabbit(sm->getRabbitSpawnTwo(),
                   sm->getDungeonMap());

        new Crocodile(sm->getCrocSpawnOne(),
                      sm->getDungeonMap());
        new Crocodile(sm->getCrocSpawnTwo(),
                      sm->getDungeonMap());

        start_game_loop();

    } catch (const std::out_of_range &oor) {
        std::cout << "Quit: " << oor.what() << std::endl;
    }

    // Memory management - cleanup
    for (size_t i = 0; i < GAME_OBJECTS.size(); ++i) {
        delete GAME_OBJECTS[i];
    }

    ACTORS.clear();
    GAME_OBJECTS.clear();

    return EXIT_SUCCESS;
}
