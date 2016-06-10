// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_DUNGEON_MAP_HPP_
#define LAB3_DUNGEON_MAP_HPP_

#include <string>
#include <map>
#include <stdexcept>
#include <memory>

#include "Environment.hpp"
#include "Direction.hpp"

namespace dnd {

typedef std::vector< std::pair<Environment *, Direction> > Exits;
typedef std::map<Environment*, Exits> EnvironmentMap;

class DungeonMap {
 private:
    EnvironmentMap env_map;

    public:

    DungeonMap() {}

    void add_exit(Environment *from,
                  Environment *to,
                  const Direction direction) {
        auto it = this->env_map.find(from);
        if (it == this->env_map.end()) {
            auto pp = this->env_map.insert(std::make_pair(from, Exits(0)));
            it = pp.first;
        }

        for (auto &p : (*it).second) {
            if (p.first == to) {
                throw std::invalid_argument("Already added this type of exit.");
            }
        }

        (*it).second.push_back( std::make_pair(to, direction) );
    }

    void ew(Environment *east,
            Environment *west) {
        this->add_exit(east, west, WEST);
        this->add_exit(west, east, EAST);
    }

    void ns(Environment *north,
            Environment *south) {
        this->add_exit(north, south, SOUTH);
        this->add_exit(south, north, NORTH);
    }

    void ud(Environment *up,
            Environment *down) {
        this->add_exit(up, down, DOWN);
        this->add_exit(down, up, UP);
    }

    std::shared_ptr<std::vector<Direction>> exits(Environment *env) {
        std::shared_ptr<std::vector<Direction>> res = std::make_shared<std::vector<Direction>>();
        auto it = this->env_map.find(env);
        if (it == this->env_map.end()) {
            return res;
        }
        for (auto &p : (*it).second) {
            res->push_back(p.second);
        }
        return res;
    }

    Environment *env_from_exit(Environment *from, Direction dir) const {
        auto it = this->env_map.find(from);
        if (it == this->env_map.end()) {
            throw std::invalid_argument("Can't find any exits.");
        }

        for (auto &p : (*it).second) {
            if (p.second == dir) {
                return p.first;
            }
        }
        throw std::invalid_argument("No exit in given direction.");
    }

};
} // namespace dnd

#endif  // LAB3_DUNGEON_MAP_HPP_
