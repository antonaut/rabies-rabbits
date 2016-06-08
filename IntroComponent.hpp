#ifndef LAB3_INTROCOMPONENT_HPP_
#define LAB3_INTROCOMPONENT_HPP_

#include <iostream>
#include <string>
#include <stdexcept>

#include "Component.hpp"
#include "EventBus.hpp"
#include "CharacterRace.hpp"
#include "CharacterClass.hpp"

#include "PlayerComponent.hpp"
#include "HealthComponent.hpp"

#include "Player.hpp"

namespace dnd {

    class IntroComponent : public Component {
        private:
        EventBus *ebp;
        IntroComponent() = delete;

        std::string get_string() {
            try {
                std::string line;
                if (!std::getline(std::cin, line)) {
                    throw std::out_of_range("Ctrl-D");
                }
                return line;
            } catch (const std::invalid_argument &exception) {
                return "";
            }
        }

        int get_integer() {
            try {
                std::string line;
                if (!std::getline(std::cin, line)) {
                    throw std::out_of_range("Ctrl-D");
                }
                int res = std::stoi(line, nullptr);
                return res;
            } catch (const std::invalid_argument &exception) {
                return 0;
            }
        }

        public:
        IntroComponent(EventBus *ebp) :
            Component(ComponentType::INTRO),
            ebp(ebp) {}


        CharacterRace& pickRace() {
            int i = 1, choice;
            while (true) {
                std::cout << "Please pick a race by entering a number:" << std::endl << std::endl;
                i = 1;
                for (auto &r : character_races) {
                    std::cout << i << ": " << r << std::endl;
                    ++i;
                }
                std::cout << std::endl << ">";
                choice = this->get_integer();
                if (choice > 0 && ((size_t) choice) <= character_races.size()) {
                    return character_races[choice - 1];
                }
                std::cout << "No such race available." << std::endl;
            }
        }

        CharacterClass& pickClass() {
            int i,choice;
            while (true) {
                std::cout << "Please pick a class by entering a number:" << std::endl << std::endl;
                i = 1;
                for (auto &c : character_classes) {
                    std::cout << i << ": " << c << std::endl;
                    ++i;
                }
                std::cout << std::endl << ">";
                choice = this->get_integer();
                if (choice > 0 && ((size_t) choice) <= character_classes.size()) {
                    return character_classes[choice - 1];
                }
            }
        }

      Player* create_player() {
            std::string name;
            std::cout << "What is your name?" << std::endl;
            std::cout << ">";
            name = get_string();
            std::cout << std::endl;

            CharacterRace& race = this->pickRace();
            CharacterClass& cls = this->pickClass();

            PlayerComponent *player_comp = new PlayerComponent(name, race, cls);
            HealthComponent *health_comp = new HealthComponent(100);

            std::cout << "Welcome to kaninskogen, " <<
                name <<
                " the " <<
                race << "-" <<
                cls << "." <<
                std::endl << "Your goal is to beat the badass bunny." <<
                std::endl;

            return new Player(this->ebp, player_comp, health_comp);
        }

        void play() {
        }
    };

}  // namespace dnd


#endif  // LAB3_INTROCOMPONENT_HPP_
