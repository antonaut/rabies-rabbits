// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_DUNGEON_MAP_HPP_
#define LAB3_DUNGEON_MAP_HPP_

#include <string>
#include <map>
#include <stdexcept>
#include <memory>
#include <deque>

#include "Environment.hpp"
#include "Direction.hpp"

namespace lab3 {

typedef std::vector<std::pair<const Environment *, Direction> > Exits;
typedef std::map<const Environment *, Exits> EnvironmentMap;

class DungeonMap {
 private:
  EnvironmentMap env_map;

 public:

  DungeonMap() { }

  void add_exit(const Environment *from,
                const Environment *to,
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

    (*it).second.push_back(std::make_pair(to, direction));
  }

  void ew(const Environment *east,
          const Environment *west) {
    this->add_exit(east, west, WEST);
    this->add_exit(west, east, EAST);
  }

  void ns(const Environment *north,
          const Environment *south) {
    this->add_exit(north, south, SOUTH);
    this->add_exit(south, north, NORTH);
  }

  void ud(const Environment *up,
          const Environment *down) {
    this->add_exit(up, down, DOWN);
    this->add_exit(down, up, UP);
  }

  std::vector<Direction> exits(const Environment *env) const {
    std::vector<Direction> res;
    auto it = this->env_map.find(env);
    if (it == this->env_map.end()) {
      return res;
    }
    for (auto &p : (*it).second) {
      res.push_back(p.second);
    }
    return res;
  }

  const Environment *the_void = (const Environment *) 0;
  std::pair<const Environment *, Direction> BOGUS = std::make_pair(the_void, NORTH);

  std::vector<Direction> backtrack(const Environment *from, const Environment *to,
                                   std::map<const Environment *, std::pair<const Environment *, Direction>> prev) {

    std::vector<lab3::Direction> path;
    const Environment *current = to;
    while (prev[current].first != the_void) {
      path.push_back(prev[current].second);
      current = prev[current].first;
    }
    return path;
  }

  std::vector<Direction> bfs(const Environment *from, const Environment *to, DungeonMap *dmap) {
    std::set<const Environment *> visited;

    const Environment *current = from;

    std::map<const Environment *, std::pair<const Environment *, Direction>> previous;
    previous[current] = BOGUS;

    std::deque<const Environment *> queue;
    queue.push_back(current);

    while (!queue.empty()) {
      current = *queue.begin();
      visited.insert(current);

      if (current == to) {
        return this->backtrack(from, to, previous);
      }

      queue.pop_front();
      std::vector<Direction> exits = dmap->exits(current);
      std::vector<const Environment *> nextRooms;
      for (size_t i = 0; i < exits.size(); ++i) {
        Direction next_dir = exits[i];
        const Environment *next_env = dmap->env_from_exit(current, next_dir);
        if (visited.find(next_env) == visited.end()) { // not visited
          nextRooms.push_back(next_env);
          previous.insert(std::make_pair(next_env, std::make_pair(current, next_dir)));
        }
      }
      queue.insert(queue.end(), nextRooms.begin(), nextRooms.end());
    }
    return std::vector<Direction>();
  }


  const Environment *env_from_exit(const Environment *from, Direction dir) const {
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
} // namespace lab3

#endif  // LAB3_DUNGEON_MAP_HPP_
