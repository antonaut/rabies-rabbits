// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_REPL_HPP_
#define LAB3_REPL_HPP_

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdexcept>

#include "GameObject.hpp"
#include "Player.hpp"
#include "TickCount.hpp"

namespace dnd {

    typedef std::vector<std::string> Tokens;

    struct Repl : public GameObject {
    private:
        void split(std::string str, char delim, std::vector<std::string> &elems) {
            std::stringstream ss(str);
            std::string item;
            while (std::getline(ss, item, delim)) {
                if (!item.empty()) {
                    elems.push_back(item);
                }
            }
        }

        Player *player;
    public:
        Repl(Player *p) : GameObject(), player(p) { }

        virtual void action() {

            // Read -> Eval -> Print -> Loop => REPL

            std::cout << this->player->get_name() << " - "
            << this->player->getCurrent_health()
            << "/" << this->player->max_health << ">";
            std::string command_input;
            std::getline(std::cin, command_input);

            if (std::cin.eof()) {
                throw std::out_of_range("Ctrl-D"); // Quit game
            }

            Tokens tokens;
            this->split(command_input, ' ', tokens);

            try {
                this->parse(tokens);
            } catch (std::exception &ex) {
                std::cout << "Arglebargle, glop-glyf!?!" << std::endl;
            }
        }


        void parse(Tokens &tokens) {
            if (tokens.empty()) return;
            this->look(tokens);
        }


        inline void playerLook() {
            std::clog << "player look" << std::endl;
            std::cout << player->position->name << std::endl;
            for (size_t i = 0; i < player->position->name.size(); i++) {
                std::cout << "=";
            }
            std::cout << std::endl << player->position->short_description << std::endl;

            for (auto &actor : findActorsByPosition(player->position)) {
                if (actor->id != player_id)
                    std::cout << "[" << actor->id << "] - A " << actor->race << " is here." << std::endl;
            }

            this->printExits();
        }

        void printExits() const {
            std::cout << "Exits: ";
            std::vector<Direction> exits = player->game_map->exits(player->position);

            if (exits.size() > 1) {
                for (size_t i = 0; i < exits.size() - 1; ++i) {
                    std::cout << exits[i] << ", ";
                }
            }
            std::cout << exits[exits.size() - 1];
            std::cout << std::endl;
        }

        inline void look(Tokens &tokens) {
            if (*tokens.begin() == "look") {
                this->playerLook();
                return;
            }
            this->inventory(tokens);
        }

        inline void inventory(Tokens &tokens) {
            if (*tokens.begin() == "inv" ||
                *tokens.begin() == "inventory") {
                return;
            }
            this->help(tokens);
        }


        inline void help(Tokens &tokens) {
            if (*tokens.begin() == "help") {
                std::cout << "There are only a few commands:" << std::endl
                << "    help - prints this help." << std::endl
                << "    look - look around you." << std::endl
                << "    go *dir* - walk in direction: " << std::endl
                << "        *dir* can be any from " << std::endl
                << std::endl
                << "        \"north\", \"south\"" << std::endl
                << "        \"west\", \"east\"" << std::endl
                << "        \"up\", \"down\"" << std::endl
                << std::endl
                << std::endl
                << "Objects in the game are shown with their id."
                << std::endl
                << "Example:"
                << std::endl
                << "    [32] - Bird, where '32' is the id of the bird."
                << std::endl
                << std::endl
                << "In order to interact with the objects, simply use their id after the interaction."
                << std::endl
                << "Example:"
                << std::endl
                << "    '>fight 32'  -- fights with the bird"
                << std::endl
                << std::endl
                << "Interaction commands:"
                << std::endl
                << "    talk *target* - talks to *target*." << std::endl
                << "    fight *target* - fights with *target*." << std::endl
                << "    take *item* - takes *item*." << std::endl
                << "    inv - lists item in inventory." << std::endl
                << std::endl
                << "Press `Ctrl-d` to quit the game." << std::endl;
                return;
            }
            this->go(tokens);
        }


        inline void go(Tokens &tokens) {
            if (*tokens.begin() == "go" ||
                *tokens.begin() == "g") {
                auto it = ++tokens.begin();
                std::clog << "player go" << std::endl;
                bool moved;
                if (tokens.size() == 1) {
                    std::cout << "Go in what direction?" << std::endl;
                    return;
                }
                try {
                    auto dir = parseDirection(*it);
                    moved = this->player->go(dir);
                } catch (std::exception &ex) {
                    moved = false;
                }

                if (moved) {
                    this->playerLook();
                    ++tickCount;
                } else {
                    std::cout << "Unable to move in that direction." << std::endl;
                }

                return;
            }
            this->fight(tokens);
        }


        inline void fight(Tokens &tokens) {
            if (*tokens.begin() == "fight" ||
                *tokens.begin() == "kill" ||
                *tokens.begin() == "k") {

                auto it = ++tokens.begin();
                std::clog << "player fight " << *it << std::endl;
                uint64_t target_id = std::stoull(*it);
                GameObject *target;
                try {
                    target = findGameObjectById(target_id);
                } catch (const std::invalid_argument &ex) {
                    std::cout << "No such target found." << std::endl;
                    return;
                }
                Actor *targetActor = (Actor *) target;
                if (targetActor->position == this->player->position) {
                    this->player->fight(targetActor);
                    ++tickCount;
                    return;
                }
                std::cout << "No such target found." << std::endl;
                return;
            }
            this->talk(tokens);
        }


        inline void talk(Tokens &tokens) {
            if (*tokens.begin() == "talk") {
                auto it = ++tokens.begin();
                std::clog << "player talk " << *it << std::endl;
                return;
            }
            this->take(tokens);
        }

        inline void take(Tokens &tokens) {
            if (*tokens.begin() == "take") {
                auto it = ++tokens.begin();
                std::clog << "player take " << *it << std::endl;
                return;
            }
            this->wait(tokens);
        }

        inline void wait(Tokens &tokens) {
            if (*tokens.begin() == "wait") {
                std::clog << "player wait" << std::endl;
                ++tickCount;
                return;
            }
            throw std::invalid_argument("Argle.");
        }

    };

}  // namespace dnd


#endif  // LAB3_REPL_HPP_
