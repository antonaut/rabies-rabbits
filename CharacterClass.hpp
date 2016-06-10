#ifndef LAB3_CHARACTER_CLASS_HPP_
#define LAB3_CHARACTER_CLASS_HPP_

#include <iostream>
#include <string>
#include <vector>


namespace dnd {

    struct CharacterClass {
        std::string name;

        friend std::ostream &operator<<(std::ostream &str, const CharacterClass c);

    };

    std::ostream &operator<<(std::ostream &str, const CharacterClass c) {
        str << c.name;
        return str;
    }

    std::vector<CharacterClass> character_classes = {
            CharacterClass{"Vet"},
            CharacterClass{"C++ programmer"},
            CharacterClass{"Electrician"}
    };

    CharacterClass CLASS_ENEMY{"Enemy"};


}  // namespace dnd


#endif  // LAB3_CHARACTER_CLASS_HPP_
