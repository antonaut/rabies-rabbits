// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_SMALL_GAME_MAP_HPP_
#define LAB3_SMALL_GAME_MAP_HPP_

#include "GameObject.hpp"
#include "Environment.hpp"
#include "DungeonMap.hpp"

namespace lab3 {

    class SmallGameMap : public GameObject {
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
        SmallGameMap() : GameObject() {

            big_rock = new Environment(FOREST_TYPE, "A big glowing rock",
                                       "You stand in front of a big rock.\n"
                                               "Somehow you feel like resting next to the stone makes you healthier."),
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
                                                "The air is filled with flies and mosquitoes."),
            swamp_two = new Environment(SWAMP_TYPE, "A muddy swamp",
                                        "There is mud and water everywhere.\n"
                                                "The air is filled with flies and mosquitoes."),
            swamp_three = new Environment(SWAMP_TYPE, "A muddy swamp",
                                          "There is mud and water everywhere.\n"
                                                  "The air is filled with flies and mosquitoes."),
            swamp_four = new Environment(SWAMP_TYPE, "A muddy swamp",
                                         "There is mud and water everywhere.\n"
                                                 "The air is filled with flies and mosquitoes."),
            mountain_one = new Environment(MOUNTAIN_TYPE, "The bottom of the mountain",
                                           "The mountain is pretty steep. The vegetation is not as dense anymore."),
            mountain_two = new Environment(MOUNTAIN_TYPE, "Halfway up the mountain",
                                           "A small river runs down the side. The top is visible from here."),
            mountain_three = new Environment(MOUNTAIN_TYPE, "The top of the mountain",
                                             "The view up here is breathtaking.");

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

            this->dm.ns(swamp_four, mountain_one);
            this->dm.ud(mountain_two, mountain_one);
        }

        ~SmallGameMap() { }

        SmallGameMap(const SmallGameMap &sfm) = delete;

        SmallGameMap &operator=(const SmallGameMap &sfm) = delete;

        const Environment *getStart() const {
            return big_rock;
        }

        const Environment *getRabbitSpawnOne() const {
            return forest_three;
        }

        const Environment *getRabbitSpawnTwo() const {
            return forest_seven;
        }

        const Environment *getCrocSpawnOne() const {
            return swamp_two;
        }

        const Environment *getCrocSpawnTwo() const {
            return swamp_four;
        }

        DungeonMap *getDungeonMap() {
            return &this->dm;
        }

        const Environment *getBossSpawn() const {
            return mountain_two;
        }

        void addFinalExit() {
            this->dm.ud(mountain_three, mountain_two);
        }
    };


} // namespace lab3

#endif  // LAB3_SMALL_GAME_MAP_HPP_
