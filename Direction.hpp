// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_DIRECTION_HPP_
#define LAB3_DIRECTION_HPP_

#include <string>
#include <set>
#include <sstream>

namespace dnd {

    typedef std::string Direction;

    const Direction EAST = "E";
    const Direction WEST = "W";
    const Direction NORTH = "N";
    const Direction SOUTH = "S";
    const Direction UP = "U";
    const Direction DOWN = "D";

    const std::set<Direction> DIRECTIONS() {
        std::set<Direction> dirs;

        dirs.insert(EAST);
        dirs.insert(WEST);
        dirs.insert(NORTH);
        dirs.insert(SOUTH);
        dirs.insert(UP);
        dirs.insert(DOWN);
        return dirs;
    }


    Direction parseDirection(std::string dir) {
        char c = *dir.begin();
        std::locale loc;
        std::stringstream ss;
        ss << std::toupper(c, loc);

        if (DIRECTIONS().find(ss.str()) != DIRECTIONS().end()) {
            return (Direction) ss.str();
        }
        throw std::invalid_argument("No such direction.");
    }

}  // namespace dnd

#endif  // LAB3_DIRECTION_HPP_
