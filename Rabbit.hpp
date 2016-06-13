#ifndef LAB3_RABBIT_HPP_
#define LAB3_RABBIT_HPP_

#include <random>
#include <set>
#include <deque>
#include "Actor.hpp"
#include "Environment.hpp"
#include "Player.hpp"
#include "CharacterClass.hpp"
#include "CharacterRace.hpp"
#include "Direction.hpp"
#include "DungeonMap.hpp"


namespace dnd {

    enum rabbit_state {
        aggr,
        wimpy
    };

    class Rabbit : public Actor {
        const Environment *starting_pos;
        int tickCount;
        rabbit_state currentState = aggr;
    public:

        Rabbit(const Environment *start_pos,
               DungeonMap *dm) : Actor(start_pos,
                                       dm,
                                       RACE_RABBIT), starting_pos(start_pos), tickCount(0) { }

        void wait() const {
            std::clog << Actor::id << " waits." << std::endl;
        }

        const Environment *the_void = (const Environment *) 0;
        std::pair<const Environment *, Direction> BOGUS = std::make_pair(the_void, NORTH);

        std::vector<Direction> backtrack(const Environment *from, const Environment *to,
                                         std::map<const Environment *, std::pair<const Environment *, Direction>> prev) {

            std::vector<dnd::Direction> path;
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
                std::shared_ptr<std::vector<Direction>> exits_ptr = dmap->exits(current);
                std::vector<const Environment *> nextRooms;
                for (size_t i = 0; i < exits_ptr->size(); ++i) {
                    Direction next_dir = (*exits_ptr)[i];
                    const Environment *next_env = dmap->env_from_exit(current, next_dir);
                    if (visited.find(next_env) != visited.end()) {
                        nextRooms.push_back(next_env);
                        previous.insert(std::make_pair(next_env, std::make_pair(current, next_dir)));
                    }
                }
                queue.insert(queue.end(), nextRooms.begin(), nextRooms.end());
            }
            return std::vector<Direction>();
        }

        void moveTowards(const Environment *target_location) {
            std::vector<Direction> path = this->bfs(Actor::position, target_location, Actor::game_map);
            if (path.empty()) {
                return this->wait();
            }

            std::clog << Actor::id << " - move towards path ";
            for (Direction d : path) {
                std::clog << d << ", ";
            }
            std::clog << std::endl;

            this->go(*path.begin());
        }

        // Flee in a random direction
        void flee() {
            const std::shared_ptr<std::vector<Direction>> &ptr = this->game_map->exits(this->position);
            std::mt19937 mt_engine;
            std::uniform_int_distribution<int> distribution(0, (int) ptr->size() - 1);
            int exit_index = distribution(mt_engine);

            this->go((*ptr)[exit_index]);
        }

        virtual void action() {
            if (tickCount % 3 == 0) {
                if (currentState == aggr) {
                    Player *player = getPlayer();
                    if (player->position == Actor::position) {
                        Actor::fight(player);
                        return;
                    }
                    this->moveTowards(player->position);
                    ++tickCount;
                    return;
                } else {
                    this->flee();
                    ++tickCount;
                    return;
                }
            } else {
                wait();
            }

            if (Actor::current_health < Actor::current_health) {
                currentState = wimpy;
            }
            ++tickCount;

        }
    };


}  // namespace dnd


#endif  // LAB3_RABBIT_HPP_
