// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include <string>
#include <iostream>

#include "tezt.hpp"
#include "Environment.hpp"
#include "DungeonMap.hpp"
#include "Rabbit.hpp"
#include "Crocodile.hpp"
#include "SmallGameMap.hpp"

using namespace lab3;


int main(int argc, char const *argv[]) {
    const Environment
            big_rock(FOREST_TYPE, "A big rock",
                     "You stand in front of a big rock. Somehow you feel like home."),
            forest_one(FOREST_TYPE, "In the forest",
                       "You find yourself lost amongst the trees."),
            forest_two(FOREST_TYPE, "In the forest",
                       "You find yourself lost amongst the trees."),
            forest_three(FOREST_TYPE, "In the forest",
                         "You find yourself lost amongst the trees."),
            forest_four(FOREST_TYPE, "In the forest",
                        "You find yourself lost amongst the trees."),
            forest_five(FOREST_TYPE, "In the forest",
                        "You find yourself lost amongst the trees."),
            forest_six(FOREST_TYPE, "In the forest",
                       "You find yourself lost amongst the trees."),
            forest_seven(FOREST_TYPE, "In the forest",
                         "You find yourself lost amongst the trees."),
            forest_eight(FOREST_TYPE, "In the forest",
                         "You find yourself lost amongst the trees."),
            forest_nine(FOREST_TYPE, "In the forest",
                        "You find yourself lost amongst the trees. There's a light up there.");

    DungeonMap dm;

    dm.ns(&big_rock, &forest_one);
    dm.ns(&forest_one, &forest_two);
    dm.ns(&forest_two, &forest_three);

    dm.ew(&forest_three, &forest_four);
    dm.ns(&forest_five, &forest_four);
    dm.ns(&forest_six, &forest_five);

    dm.ew(&forest_six, &forest_seven);
    dm.ns(&forest_seven, &forest_eight);
    dm.ns(&forest_eight, &forest_nine);

    dm.add_exit(&forest_nine, &big_rock, UP);

    tezt::add("Create a map.", [&] {
        auto f7_exits = dm.exits(&forest_seven);
        tezt::ae((size_t) 2, f7_exits.size());

        auto f9_exits = dm.exits(&forest_nine);
        tezt::ae((size_t) 2, f9_exits.size());

        auto big_rock_exits = dm.exits(&big_rock);
        tezt::ae((size_t) 1, big_rock_exits.size());
    });

    tezt::add("Player movement", [&] {
        Player *player = new Player(&big_rock, &dm, "Anton", &character_races[1], character_classes[1]);
        Repl repl(player);
        std::vector<std::string> tokens({"go", "south"});
        repl.parse(tokens);
        tezt::ae(&forest_one, player->position);

        delete player;
    });

    tezt::add("Player look", [&] {
        Player *player = new Player(&big_rock, &dm, "Testy", &character_races[0], character_classes[2]);
        Repl *repl = new Repl(player);
        std::vector<std::string> tokens({"look"});
        repl->parse(tokens);
    });

    tezt::add("Remove dead actor after an action is performed that kills it.", [&] {

        Player *player = new Player(&big_rock, &dm, "Testy", &character_races[0], character_classes[2]);
        Actor *rabbit = new Rabbit(&forest_four, &dm);
        auto s1 = ACTORS.size();

        rabbit->current_health = 1;

        // Simulate GameLoop
        player->fight(rabbit);

        tezt::ae(true, rabbit->is_dead, "Rabbit should be dead.");

        // Make sure rabbit is gone
        for (auto it = ACTORS.begin(); it != ACTORS.end(); ++it) {
            if ((*it)->is_dead) {
                ACTORS.erase(it);
                break;
            }
        }

        tezt::ae(s1 - 1, ACTORS.size(), "One less actor than before.");
        tezt::ae((uint32_t) 0, rabbit->current_health, "Dead enemies have zero hp left. Nothing else.");
    });

    tezt::add("A crocodile is slower than a rabbit on land, but faster in water!", [&] {
        Rabbit r1(&big_rock, &dm);
        Crocodile c1(&big_rock, &dm);
        Player player(&forest_nine, &dm, "Testy", &character_races[2], character_classes[0]);

        const Environment *target = &forest_nine;

        while (r1.position->id != target->id) {
            r1.action();
            c1.action();
            tickCount++;
        }

        tezt::ae(target->id, r1.position->id, "Rabbit arrived at target.");
        tezt::ane(target->id, c1.position->id, "Crocodile not at target.");
    });

    tezt::add("A crocodile is faster in the swamp.", [&] {
        SmallGameMap *sm2 = new SmallGameMap();
        Rabbit r1(sm2->getCrocSpawnOne(), sm2->getDungeonMap());
        Crocodile c1(sm2->getCrocSpawnOne(), sm2->getDungeonMap());
        Player player(sm2->getCrocSpawnTwo(), sm2->getDungeonMap(), "Testy", &character_races[2], character_classes[0]);

        r1.position = sm2->getCrocSpawnOne();
        c1.position = sm2->getCrocSpawnOne();
        player.position = sm2->getCrocSpawnTwo();

        const Environment *target = player.position;

        while (c1.position->id != target->id) {
            r1.action();
            c1.action();
            tickCount++;
        }

        tezt::ae(target->id, c1.position->id, "The croc is at target.");
        tezt::ane(target->id, r1.position->id, "...But the rabbit isn't.");
    });

    tezt::add("A crocodile always hurts more than a rabbit.", [&] {
        Race dummy{"Dummy"};

        Actor dummy1(&big_rock, &dm, &dummy);
        Actor dummy2(&big_rock, &dm, &dummy);

        Crocodile crocodile(&big_rock, &dm);
        Rabbit rabbit(&big_rock, &dm);

        rabbit.fight(&dummy1);
        crocodile.fight(&dummy2);

        tezt::ae(true, dummy1.getCurrent_health() < dummy2.getCurrent_health());
    });

    return tezt::run();
}
