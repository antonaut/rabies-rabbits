// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_SMALL_FOREST_MAP_HPP_
#define LAB3_SMALL_FOREST_MAP_HPP_

#include "GameObject.hpp"
#include "Environment.hpp"
#include "DungeonMap.hpp"

namespace dnd {

    class SmallForestMap {
    private:
        Environment *big_rock,
                *forest_one,
                *forest_two,
                *forest_three,
                *forest_four,
                *forest_five,
                *forest_six,
                *forest_seven,
                *forest_eight,
                *forest_nine,
                *swamp_one,
                *swamp_two,
                *swamp_three,
                *swamp_four,
                *mountain_one,
                *mountain_two,
                *mountain_three;
        DungeonMap dm;
    public:
        SmallForestMap() : GameObject() {

            big_rock = new Environment(FOREST_TYPE, "A big rock",
                                                "You stand in front of a big rock. Somehow you feel like home."),
            forest_one = new Environment(FOREST_TYPE, "In the forest",
                                         "You find yourself lost amongst the trees."),
            forest_two = new Environment(FOREST_TYPE, "In the forest",
                                         "You find yourself lost amongst the trees."),
            forest_three = new Environment(FOREST_TYPE, "In the forest",
                                           "You find yourself lost amongst the trees."),
            forest_four = new Environment(FOREST_TYPE, "In the forest",
                                          "You find yourself lost amongst the trees."),
            forest_five = new Environment(FOREST_TYPE, "In the forest",
                                          "You find yourself lost amongst the trees."),
            forest_six = new Environment(FOREST_TYPE, "In the forest",
                                         "You find yourself lost amongst the trees."),
            forest_seven = new Environment(FOREST_TYPE, "In the forest",
                                           "You find yourself lost amongst the trees."),
            forest_eight = new Environment(FOREST_TYPE, "In the forest",
                                           "You find yourself lost amongst the trees."),
            forest_nine = new Environment(FOREST_TYPE, "In the forest",
                                          "You find yourself lost amongst the trees.\n"
                                                  "There's a small opening over there."),
            swamp_one = new Environment(SWAMP_TYPE, "A muddy swamp",
                                        "The vegetation changes. It is a bit less dense, but now there is mud everywhere.\n"
                                                "The air is filled with flies and mosquitoes.\n"),
            swamp_two = new Environment(SWAMP_TYPE, "A muddy swamp",
                                        "There is mud and water everywhere.\n"
                                                "The air is filled with flies and mosquitoes.\n"),
            swamp_three = new Environment(SWAMP_TYPE, "A muddy swamp",
                                          "There is mud and water everywhere.\n"
                                                  "The air is filled with flies and mosquitoes.\n"),
            swamp_four = new Environment(SWAMP_TYPE, "A muddy swamp",
                                         "There is mud and water everywhere.\n"
                                                 "The air is filled with flies and mosquitoes.\n"),
            mountain_one = new Environment(MOUNTAIN_TYPE, "The bottom of the mountain",
                                           "The mountain is steep and ");

            this->dm.ns(big_rock, forest_one);
            this->dm.ns(forest_one, forest_two);
            this->dm.ns(forest_two, forest_three);

            this->dm.ew(forest_three, forest_four);
            this->dm.ns(forest_five, forest_four);
            this->dm.ns(forest_six, forest_five);

            this->dm.ew(forest_six, forest_seven);
            this->dm.ns(forest_seven, forest_eight);
            this->dm.ns(forest_eight, forest_nine);

            this->dm.ew(forest_nine, swamp_one);
            this->dm.ns(swamp_one, swamp_two);
            this->dm.ew(swamp_two, swamp_three);
            this->dm.ns(swamp_three, swamp_four);

        }

        ~SmallForestMap() {
            Environment *big_rock,
                    *forest_one,
                    *forest_two,
                    *forest_three,
                    *forest_four,
                    *forest_five,
                    *forest_six,
                    *forest_seven,
                    *forest_eight,
                    *forest_nine,
                    *swamp_one,
                    *swamp_two,
                    *swamp_three,
                    *swamp_four;
        }

        SmallForestMap(const SmallForestMap &sfm) = delete;

        SmallForestMap &operator=(const SmallForestMap &sfm) = delete;

        Environment *getStart() const {
            return big_rock;
        }

        Environment *getRabbitSpawnOne() const {
            return forest_three;
        }

        Environment *getRabbitSpawnTwo() const {
            return forest_seven;
        }

        DungeonMap *getDungeonMap() {
            return &this->dm;
        }

    };

} // namespace dnd

#endif  // LAB3_SMALL_FOREST_MAP_HPP_
