// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_CROCIT_HPP
#define LAB3_CROCIT_HPP

#include "Rabbit.hpp"
#include "Crocodile.hpp"

namespace dnd {

    class Crocit : public Rabbit, public Crocodile {
    public:
        Crocit(const Environment *start, DungeonMap *dm) : Rabbit(start, dm), Crocodile(start, dm) { }
    };


}

#endif // LAB3_CROCIT_HPP
