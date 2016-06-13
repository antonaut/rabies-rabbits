// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_SMALL_FOREST_MAP_HPP_
#define LAB3_SMALL_FOREST_MAP_HPP_

#include "GameObject.hpp"
#include "Environment.hpp"
#include "DungeonMap.hpp"

namespace dnd {

    class SmallForestMap : public GameObject {
    private:
        Environment *start, *r1, *r2;
        DungeonMap dm;
    public:
        SmallForestMap() : GameObject() {
            Environment
                    *big_rock = new Environment("A big rock",
                                                "You stand in front of a big rock. Somehow you feel like home."),
                    *forest_one = new Environment("In the forest",
                                                  "You find yourself lost amongst the trees."),
                    *forest_two = new Environment("In the forest",
                                                  "You find yourself lost amongst the trees."),
                    *forest_three = new Environment("In the forest",
                                                    "You find yourself lost amongst the trees."),
                    *forest_four = new Environment("In the forest",
                                                   "You find yourself lost amongst the trees."),
                    *forest_five = new Environment("In the forest",
                                                   "You find yourself lost amongst the trees."),
                    *forest_six = new Environment("In the forest",
                                                  "You find yourself lost amongst the trees."),
                    *forest_seven = new Environment("In the forest",
                                                    "You find yourself lost amongst the trees."),
                    *forest_eight = new Environment("In the forest",
                                                    "You find yourself lost amongst the trees."),
                    *forest_nine = new Environment("In the forest",
                                                   "You find yourself lost amongst the trees. There's a light up there.");
            start = big_rock;
            r1 = forest_four;
            r2 = forest_seven;


            this->dm.ns(big_rock, forest_one);
            this->dm.ns(forest_one, forest_two);
            this->dm.ns(forest_two, forest_three);

            this->dm.ew(forest_three, forest_four);
            this->dm.ns(forest_five, forest_four);
            this->dm.ns(forest_six, forest_five);

            this->dm.ew(forest_six, forest_seven);
            this->dm.ns(forest_seven, forest_eight);
            this->dm.ns(forest_eight, forest_nine);

            this->dm.add_exit(forest_nine, big_rock, UP);

        }

        ~SmallForestMap() {

        }

        SmallForestMap(const SmallForestMap &sfm) = delete;

        SmallForestMap &operator=(const SmallForestMap &sfm) = delete;

        Environment *getStart() const {
            return start;
        }

        Environment *getRabbitSpawnOne() const {
            return r1;
        }

        Environment *getRabbitSpawnTwo() const {
            return r2;
        }

        DungeonMap *getDungeonMap() {
            return &this->dm;
        }

    };

} // namespace dnd

#endif  // LAB3_SMALL_FOREST_MAP_HPP_
