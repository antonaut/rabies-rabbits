#ifndef LAB3_CHARACTER_CLASS_HPP_
#define LAB3_CHARACTER_CLASS_HPP_

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>


namespace lab3 {

struct CharacterClass {
  std::string name;
  std::function<void(std::string, uint32_t, uint32_t, uint32_t)> attack_fn;
  std::function<void(std::string)> killed_fn;
  friend std::ostream &operator<<(std::ostream &str, const CharacterClass c);

};

std::ostream &operator<<(std::ostream &str, const CharacterClass c) {
  str << c.name;
  return str;
}

std::vector<CharacterClass> character_classes = {
    CharacterClass{"Veterinarian",
                   [&](std::string target,
                       uint32_t max_hp,
                       uint32_t current_hp,
                       uint32_t dmg) {
                     double diff = max_hp - current_hp;
                     std::cout << "You stab "
                         << target << " with a syringe and put in "
                         << dmg
                         << " drops of vaccine. Sickness cured by "
                         << std::setprecision(3)
                         << (diff / (double) max_hp) * 100.0 << "%." << std::endl;
                   },
                   [&](std::string target) {
                     std::cout << "Nursed "
                         << target
                         << " back to full health. It ran hom-to-mom-nom-nom." << std::endl;
                   }},
    CharacterClass{"C++ programmer",
                   [&](std::string target,
                       uint32_t max_hp,
                       uint32_t current_hp,
                       uint32_t dmg) {
                     double diff = max_hp - current_hp;
                     std::cout << "You put an effort worth "
                         << dmg
                         << " points into solving " << std::endl
                         << target << "'s problems. "
                         << std::setprecision(3)
                         << (diff / (double) max_hp) * 100.0 << "% of corner cases covered." << std::endl;
                   },
                   [&](std::string target) {
                     std::cout << "I guess "
                         << target
                         << " won't be a problem any more." << std::endl;
                   }
    },
    CharacterClass{"Electrician",
                   [&](std::string target,
                       uint32_t max_hp,
                       uint32_t current_hp,
                       uint32_t dmg) {
                     std::cout << "You shock "
                         << target << " with a tazer for "
                         << dmg << " points of damage. "
                         << std::setprecision(3)
                         << ((double) current_hp / (double) max_hp) * 100.0 << "% health left." << std::endl;
                   },
                   [&](std::string target) {
                     std::cout << "It smells of electrocuted flesh after " << target << "." << std::endl;
                   }
    }
};

CharacterClass CLASS_ENEMY{"Enemy"};

}  // namespace lab3


#endif  // LAB3_CHARACTER_CLASS_HPP_
