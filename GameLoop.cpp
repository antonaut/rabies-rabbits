// Copyright 2016 Anton Erholt <aerholt@kth.se>

// #include <iostream>
#include <string>
// #include <chrono>
#include <cstdlib>
#include <vector>

#include "GameObject.hpp"
#include "EventBus.hpp"
#include "SmallForestMap.hpp"
#include "REPL.hpp"
#include "Intro.hpp"

namespace dnd {

    std::vector<GameObject*> game_objects;

    void start_game_loop() {
        /*
        std::chrono::time_point<std::chrono::system_clock> delta = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> last_time = std::chrono::system_clock::now();
        */
        for (;;) {
            // std::chrono::duration<double> delta
            // = std::chrono::system_clock::now() - last_time;
            for (auto &game_obj : game_objects) {
                // game_obj->update(delta.count());
                game_obj->fixed_update();
            }
        }
    }


}  // namespace dnd

using namespace dnd;

int main(int argc, char *argv[]) {
    (void) argv; // unused
    (void) argc; // unused

    EventBus eb;
    SmallForestMap sm(&eb);

    Intro intro(&eb);
    IntroComponent *ip = (IntroComponent*) intro.getComponent(ComponentType::INTRO);
    Player *player;
    
    try {
        ip->play();
        player = ip->create_player();
    } catch (const std::out_of_range& oor) {
        std::cout << "Quit: " << oor.what() << std::endl;
        return EXIT_SUCCESS;
    }

    
    Repl repl(&eb, player);

    //        LevelOne level_one();

    // event bus, name, race, start_location

    //        RabbitSpawner rs(&eb, 4, sm.random_forest_location());

    //        RabbitBoss(&eb, sm.finish());

    //        game_objects.push_back(&player);
    //        game_objects.push_back(&rs);

    game_objects.push_back(&sm);
    game_objects.push_back(&repl);

    start_game_loop();

    return EXIT_SUCCESS;
}
