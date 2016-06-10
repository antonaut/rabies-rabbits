// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_DIRECTION_HPP_
#define LAB3_DIRECTION_HPP_

#include <string>

namespace dnd {

    typedef std::string Direction;

    const Direction EAST = "E";
    const Direction WEST = "W";
    const Direction NORTH = "N";
    const Direction SOUTH = "S";
    const Direction UP = "U";
    const Direction DOWN = "D";

    Direction parseDirection(std::string str) {
        return UP;
    }

}  // namespace dnd

#endif  // LAB3_DIRECTION_HPP_
