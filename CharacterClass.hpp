#ifndef LAB3_CHARACTER_CLASS_HPP_
#define LAB3_CHARACTER_CLASS_HPP_

#include <iostream>
#include <string>
#include <vector>


namespace dnd {

    struct CharacterClass {
        std::string name, attack_fmt, killed_fmt;
        friend std::ostream &operator<<(std::ostream &str, const CharacterClass c);

    };

    std::ostream &operator<<(std::ostream &str, const CharacterClass c) {
        str << c.name;
        return str;
    }

    std::vector<CharacterClass> character_classes = {
            CharacterClass{"Vet",
                           "Stabs % with a syringe and empties the vaccine. Sickness cured by %\%.",
                           "Nursed % back to full health."},
            CharacterClass{"C++ programmer",
                           "Puts an effort in to solving %'s problems. %\% of corner cases covered.",
                           "I guess % won't be a problem any more."},
            CharacterClass{"Electrician",
                           "Shocks % with a tazer. %\% health left.",
                           "It smells of electrocuted flesh after %."}
    };

    CharacterClass CLASS_ENEMY{"Enemy"};


}  // namespace dnd


#endif  // LAB3_CHARACTER_CLASS_HPP_
