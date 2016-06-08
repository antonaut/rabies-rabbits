// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_DUNGEON_MAP_COMPONENT_HPP_
#define LAB3_DUNGEON_MAP_COMPONENT_HPP_

#include <string>
#include <map>
#include <stdexcept>
#include <memory>

#include "EnvironmentComponent.hpp"
#include "Component.hpp"
#include "Direction.hpp"

namespace dnd {

typedef std::vector< std::pair<const EnvironmentComponent *, Direction> > Exits;
typedef std::map<const EnvironmentComponent*, Exits> EnvironmentComponentMap;

class DungeonMapComponent : public Component {
 private:
    EnvironmentComponentMap env_map;

 public:

    DungeonMapComponent() : Component(ComponentType::DUNGEON_MAP) {}

    void add_exit(EnvironmentComponent *from,
                  EnvironmentComponent *to,
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

    void ew(EnvironmentComponent *east,
            EnvironmentComponent *west) {
        this->add_exit(east, west, WEST);
        this->add_exit(west, east, EAST);
    }

    void ns(EnvironmentComponent *north,
            EnvironmentComponent *south) {
        this->add_exit(north, south, SOUTH);
        this->add_exit(south, north, NORTH);
    }

    void ud(EnvironmentComponent *up,
            EnvironmentComponent *down) {
        this->add_exit(up, down, DOWN);
        this->add_exit(down, up, UP);
    }

    std::shared_ptr<std::vector<Direction>> exits(EnvironmentComponent *env) {
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

    const EnvironmentComponent *env_from_exit(EnvironmentComponent *from, Direction dir) {
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

#endif  // LAB3_DUNGEON_MAP_COMPONENT_HPP_
