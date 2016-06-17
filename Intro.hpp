// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_INTRO_HPP_
#define LAB3_INTRO_HPP_

#include "IOHelpers.hpp"
#include "GameObject.hpp"

namespace lab3 {

    struct Intro : public GameObject {
    private:

    public:
        Intro() : GameObject() { }

        const Race *pickRace() {
            int i, choice;
            while (true) {
                std::cout << "Please pick a race by entering a number:" << std::endl << std::endl;
                i = 1;
                for (auto &r : character_races) {
                    std::cout << i << ": " << r << std::endl;
                    ++i;
                }
                std::cout << std::endl << ">";
                choice = get_integer();
                if (choice > 0 && ((size_t) choice) <= character_races.size()) {
                    return &character_races[choice - 1];
                }
                std::cout << "No such race available." << std::endl;
            }
        }

        CharacterClass &pickClass() {
            int i, choice;
            while (true) {
                std::cout << "Please pick a class by entering a number:" << std::endl << std::endl;
                i = 1;
                for (auto &c : character_classes) {
                    std::cout << i << ": " << c << std::endl;
                    ++i;
                }
                std::cout << std::endl << ">";
                choice = get_integer();
                if (choice > 0 && ((size_t) choice) <= character_classes.size()) {
                    return character_classes[choice - 1];
                }
            }
        }

        Player *create_player(Environment *start, DungeonMap *dmap) {
            std::string name;
            std::cout << "What is your name?" << std::endl;
            std::cout << ">";
            name = get_string();
            std::cout << std::endl;

            const Race *race = this->pickRace();
            CharacterClass &cls = this->pickClass();

            std::cout << "Welcome to Arendal, "
            << name
            << " the "
            << *race
            << "-"
            << cls
            << "." << std::endl
            << "Your goal is to beat the badass crocit." << std::endl
            << "Type 'quit' to quit, type 'help' for help." << std::endl
            << std::endl;

            return new Player(start, dmap, name, race, cls);
        }

    };

}  // namespace lab3


#endif  // LAB3_INTRO_HPP_
