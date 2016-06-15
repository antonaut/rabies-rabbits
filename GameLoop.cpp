// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include <string>
#include <vector>
#include <stdexcept>

#include "GameObject.hpp"
#include "SmallForestMap.hpp"
#include "REPL.hpp"
#include "Intro.hpp"
#include "Rabbit.hpp"
#include "TickCount.hpp"

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
        }
    }

}  // namespace dnd

using namespace dnd;

int main(int argc, char *argv[]) {
    (void) argv; // unused
    (void) argc; // unused

    SmallForestMap *sm = new SmallForestMap();

    Intro *intro = new Intro();

    Player *player;

    try {
        player = intro->create_player(sm->getStart(), sm->getDungeonMap());

        Repl repl(player);

        Rabbit r1(sm->getRabbitSpawnOne(),
                  sm->getDungeonMap());
        Rabbit r2(sm->getRabbitSpawnTwo(),
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
