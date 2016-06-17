// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RABBIDILE_HPP
#define LAB3_RABBIDILE_HPP

#include "Rabbit.hpp"
#include "Crocodile.hpp"

namespace lab3 {

    class Rabbidile : public Rabbit, public Crocodile {
    public:
        Rabbidile(const Environment *start, DungeonMap *dm) : Rabbit(start, dm), Crocodile(start, dm) {

        }
    };


} // namespace lab3

#endif // LAB3_RABBIDILE_HPP
