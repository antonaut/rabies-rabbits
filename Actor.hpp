// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_ACTOR_HPP_
#define LAB3_ACTOR_HPP_

#include <cstdint>
#include <iostream>
#include <random>

#include "GameObject.hpp"
#include "Environment.hpp"
#include "Race.hpp"
#include "TickCount.hpp"
#include "Item.hpp"

namespace lab3 {

    std::mt19937 mt_engine;

    class Actor;

    std::vector<Actor *> ACTORS;

    typedef int ActorSpeed;

    const ActorSpeed SLOW(5);
    const ActorSpeed NORMAL(3);
    const ActorSpeed FAST(2);
    const ActorSpeed PRETTY_DAMN_FAST(1);

    typedef std::string ActorState;

    ActorState AGGRESSIVE("Aggressive");
    ActorState NEUTRAL("Neutral");
    ActorState WIMPY("Wimpy");


    class Actor : virtual public GameObject {
    public:

        uint32_t getCurrent_health() const {
            return this->current_health;
        }

        uint32_t getMax_health() const {
            return max_health;
        }

        const Environment *getPosition() const {
            return position;
        }

        const Race *getRace() const {
            return race;
        }

        const bool isDead() const {
            return this->is_dead;
        }

        DungeonMap *getGame_map() const {
            return game_map;
        }

    protected:
        uint32_t current_health;
        uint32_t max_health;
        uint32_t bonus_damage;
        bool bonus_applied;

        ActorSpeed speed;
        ActorState current_state = AGGRESSIVE;
        DungeonMap *game_map;
        const Race *race;

        bool is_dead;

        std::vector<Item *> inventory;

        uint32_t base_damage;
        const Environment *position;

        bool give_item_to(const uint64_t id, std::vector<Item *> &target) {
            for (auto it = this->inventory.begin(); it != this->inventory.end(); ++it) {
                auto ip = *it;
                if (ip->id == id) {
                    this->inventory.erase(it);
                    target.push_back(ip);
                    return true;
                }
            }
            return false;
        }

    public:
        Actor(const Environment *position,
              DungeonMap *game_map,
              const Race *race) :
                GameObject(),
                current_health(100),
                max_health(current_health),
                bonus_damage(0),
                bonus_applied(true),
                speed(NORMAL),
                game_map(game_map),
                race(race),
                is_dead(false),
                inventory(0),
                base_damage(10),
                position(position) {
            ACTORS.push_back(this);
        }

        virtual ~Actor() { }

        void drop(uint64_t item_id) {
            Environment *env = const_cast<Environment *>(this->position);
            this->give_item_to(item_id, env->getInventory());

        }

        virtual void heal(uint32_t amount) {
            uint64_t sum = this->current_health + amount;
            if (sum >= this->max_health) {
                this->current_health = this->max_health;
            } else {
                this->current_health = sum;
            }
        }

        virtual void hurt(uint32_t damage) {
            if (this->is_dead)
                return;
            int32_t diff = this->current_health - damage;

            if (diff <= 0) {
                this->die();
                this->current_health = 0;
                return;
            }

            this->current_health = (uint32_t) diff;
        }

        virtual void die() {
            this->howl();
            this->is_dead = true;
            std::clog << this->id << " just died." << std::endl;
        }

        virtual bool go(Direction dir) {
            const Environment *new_loc;
            try {
                new_loc = this->game_map->env_from_exit(this->position, dir);
            } catch (const std::invalid_argument &ex) {
                std::clog << ex.what();
                return false;
            }
            this->position = new_loc;
            return true;
        }

        virtual std::string noise() {
            return this->race->noise();
        }

        virtual void howl() {
            std::string n = this->noise();
            std::locale loc;
            for (std::size_t i = 0; i < n.length(); ++i) {
                std::cout << std::toupper(n[i], loc);
            }
            std::cout << std::endl;
            this->bonus_damage = 10;
            this->bonus_applied = false;
        }

        virtual uint32_t damage() {
            uint32_t total_damage = this->base_damage;

            if (!this->bonus_applied) {
                total_damage += this->bonus_damage;
                this->bonus_applied = true;
                this->bonus_damage = 0;
            }

            return total_damage;
        }

        virtual void fight(Actor *target) { }

        virtual void action() { }

        friend
        std::ostream &operator<<(std::ostream &str, const Actor &actor);

        void moveTowards(const Environment *target_location) {
            std::vector<Direction> path = this->game_map->bfs(Actor::position, target_location, Actor::game_map);
            if (path.empty()) { // already there
                return this->wait();
            }

            std::clog << Actor::id << " - move according to path ";
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                std::clog << *it << " ";
            }
            std::clog << std::endl;

            this->go(*(--path.end()));
        }

        // Flee in a random direction
        void flee() {
            std::vector<Direction> exits = this->game_map->exits(this->position);

            std::uniform_int_distribution<int> distribution(0, (int) exits.size() - 1);

            int exit_index = distribution(mt_engine);

            this->go(exits[exit_index]);
        }

        virtual void wait() const {
            std::clog << Actor::id << " waits." << std::endl;
        }

    };

    std::ostream &operator<<(std::ostream &str, const Actor &actor) {
        str << *actor.race << " [" << actor.id << "] (" << actor.current_health << "/"
        << actor.max_health << ")" << " - " << actor.current_state;
        return str;
    }

    std::vector<Actor *> findActorsByPosition(const Environment *position) {
        std::vector<Actor *> atPosition;
        for (auto &actor : ACTORS) {
            if (actor->getPosition() == position) {
                atPosition.push_back(actor);
            }
        }

        return atPosition;
    }

}  // namespace lab3


#endif  // LAB3_ACTOR_HPP_
