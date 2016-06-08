// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_SMALL_FOREST_MAP_HPP_
#define LAB3_SMALL_FOREST_MAP_HPP_

#include "GameObject.hpp"
#include "EnvironmentComponent.hpp"
#include "DungeonMapComponent.hpp"
#include "EventBus.hpp"

namespace dnd {

class SmallForestMap : public GameObject {
 private:
    //    EnvironmentComponent
 public:
    SmallForestMap(EventBus *ebp) : GameObject(ebp) {
        EnvironmentComponent
            *big_rock = new EnvironmentComponent("A big rock",
            "You stand in front of a big rock. Somehow you feel like home."),
            *forest_one = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_two = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_three = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_four = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_five = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_six = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_seven = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_eight = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees."),
            *forest_nine = new EnvironmentComponent("In the forest",
            "You find yourself lost amongst the trees. There's a light up there.");

        DungeonMapComponent dm;

        dm.ns(big_rock, forest_one);
        dm.ns(forest_one, forest_two);
        dm.ns(forest_two, forest_three);

        dm.ew(forest_three, forest_four);
        dm.ns(forest_five, forest_four);
        dm.ns(forest_six, forest_five);

        dm.ew(forest_six, forest_seven);
        dm.ns(forest_seven, forest_eight);
        dm.ns(forest_eight, forest_nine);

        dm.add_exit(forest_nine, big_rock, UP);
    }
    ~SmallForestMap() {

    }
    SmallForestMap(const SmallForestMap& sfm) = delete;
    SmallForestMap& operator=(const SmallForestMap& sfm) = delete;
};

} // namespace dnd

#endif  // LAB3_SMALL_FOREST_MAP_HPP_
