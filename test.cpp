// Copyright 2016 Anton Erholt <aerholt@kth.se>

#include <string>
#include <iostream>

// #include "GameObject.hpp"

#include "tezt.hpp"
#include "Event.hpp"
#include "EventBus.hpp"
#include "Environment.hpp"
#include "DungeonMap.hpp"

using namespace dnd;

int main(int argc, char const *argv[]) {
    Environment
        big_rock("A big rock",
        "You stand in front of a big rock. Somehow you feel like home."),
        forest_one("In the forest",
        "You find yourself lost amongst the trees."),
        forest_two("In the forest",
        "You find yourself lost amongst the trees."),
        forest_three("In the forest",
        "You find yourself lost amongst the trees."),
        forest_four("In the forest",
        "You find yourself lost amongst the trees."),
        forest_five("In the forest",
        "You find yourself lost amongst the trees."),
        forest_six("In the forest",
        "You find yourself lost amongst the trees."),
        forest_seven("In the forest",
        "You find yourself lost amongst the trees."),
        forest_eight("In the forest",
        "You find yourself lost amongst the trees."),
        forest_nine("In the forest",
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


    EventBus eb;

    tezt::add("Create a map.", [&] {
        auto f7_exits_ptr = dm.exits(&forest_seven);
        tezt::ae((size_t)2, f7_exits_ptr->size());

        auto f9_exits_ptr = dm.exits(&forest_nine);
        tezt::ae((size_t) 2, f9_exits_ptr->size());

        auto big_rock_exits_ptr = dm.exits(&big_rock);
        tezt::ae((size_t) 1, big_rock_exits_ptr->size());
    });

    return tezt::run();
}
