// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include <string>
#include <vector>
#include <stdexcept>

#include "GameObject.hpp"
#include "SmallForestMap.hpp"
#include "REPL.hpp"
#include "Intro.hpp"
#include "Rabbit.hpp"

namespace dnd {

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
            for (std::vector<Actor *>::iterator it = ACTORS.begin(); it != ACTORS.end(); ++it) {
                if ((*it)->is_dead) {
                    Actor *dead_actor = *it;
                    std::cout << dead_actor->id << " - " << dead_actor->race << " has died." << std::cout;
                    delete dead_actor;
                }
            }
        }
    }

}  // namespace dnd

using namespace dnd;

int main(int argc, char *argv[]) {

    SmallForestMap *sm = new SmallForestMap();

    Intro *intro = new Intro();

    Player *player;

    try {
        player = intro->create_player(sm->getStart(), sm->getDungeonMap());

        Repl repl(player);

        // Spawn actors, deleted upon death.
        new Rabbit(sm->getRabbitSpawnOne(),
                  sm->getDungeonMap());
        new Rabbit(sm->getRabbitSpawnTwo(),
                   sm->getDungeonMap());

        start_game_loop();

    } catch (const std::out_of_range &oor) {
        std::cout << "Quit: " << oor.what() << std::endl;
    }

    delete sm;
    delete intro;
    delete player;

    return EXIT_SUCCESS;
}
