// Copyright 2016 Anton Erholt <aerholt@kth.se>

// #include <iostream>
#include <string>
// #include <chrono>
#include <vector>
#include <stdexcept>

#include "GameObject.hpp"
#include "SmallForestMap.hpp"
#include "REPL.hpp"
#include "Intro.hpp"
#include "Rabbit.hpp"

namespace dnd {


    void start_game_loop() {
        /*
        std::chrono::time_point<std::chrono::system_clock> delta = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> last_time = std::chrono::system_clock::now();
        */
        bool quit(false);
        while (!quit) {
            // std::chrono::duration<double> delta
            // = std::chrono::system_clock::now() - last_time;
            for (auto &game_obj : GAME_OBJECTS) {
                // game_obj->update(delta.count());
                try {
                    game_obj->fixed_update();
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
