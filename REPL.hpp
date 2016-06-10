// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_REPL_HPP_
#define LAB3_REPL_HPP_

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <stdexcept>

#include "GameObject.hpp"
#include "EventBus.hpp"
#include "Player.hpp"

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
        Repl(EventBus *eb, Player *p) : GameObject(eb), player(p) { }

        virtual void fixed_update() {

            // Show prompt, REad -> Parse -> send evts/eval -> Loop => REPL

            std::cout << this->player->get_name() << " - "
            << this->player->get_health() << ">";
            std::string command_input;
            std::cin >> command_input;

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
            look(tokens);
        }


        inline void look(Tokens &tokens) {
            if (*tokens.begin() == "look") {
                GameObject::ebp->fire(&EVT_Look);
                return;
            }
            inventory(tokens);
        }

        inline void inventory(Tokens &tokens) {
            if (*tokens.begin() == "inv" ||
                *tokens.begin() == "inventory") {
                return;
            }
            help(tokens);
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
                << "    talk *target* - talks to *target*." << std::endl
                << "    fight *target* - fights with *target*." << std::endl
                << "    take *item* - takes *item*." << std::endl
                << "    inv - lists item in inventory." << std::endl
                << std::endl
                << "Press `Ctrl-c` to quit the game." << std::endl;
                return;
            }
            go(tokens);
        }


        inline void go(Tokens &tokens) {
            if (*tokens.begin() == "go" ||
                *tokens.begin() == "g") {
                auto it = ++tokens.begin();
                this->player->go(parseDirection(*it));
                return;
            }
            fight(tokens);
        }


        inline void fight(Tokens &tokens) {
            if (*tokens.begin() == "fight" ||
                *tokens.begin() == "kill" ||
                *tokens.begin() == "k") {
                auto it = ++tokens.begin();
                this->player->fight(*it);
                return;
            }
            talk(tokens);
        }


        inline void talk(Tokens &tokens) {
            if (*tokens.begin() == "talk") {
                auto it = ++tokens.begin();
                Event *talk_evt = this->player_event("PlayerTalk", *it);
                GameObject::ebp->fire(talk_evt);
                return;
            }
            take(tokens);
        }

        inline void take(Tokens &tokens) {
            if (*tokens.begin() == "take") {
                auto it = ++tokens.begin();

                return;
            }
            throw std::invalid_argument("Argle.");
        }

    };

}  // namespace dnd


#endif  // LAB3_REPL_HPP_
