#ifndef LAB3_CHARACTER_RACE_HPP_
#define LAB3_CHARACTER_RACE_HPP_

#include <string>
#include <vector>

namespace dnd {

    struct CharacterRace {
        std::string name;
        std::string sound;
        friend std::ostream& operator<<(std::ostream& str, const CharacterRace c);
        
        std::string noise() {
            return this->sound;
        }
    };

    std::ostream& operator<<(std::ostream& str, const CharacterRace c) {
        str << c.name;
        return str;
    }

    std::vector<CharacterRace> character_races = {
        CharacterRace{"Bear", "RAAWR!"},
        CharacterRace{"Fox", "Grrrr..."},
        CharacterRace{"Wolf", "GRROWL!"},
    };

    CharacterRace RACE_RABBIT{"Rabbit", "Omnomnom"};

}  // namespace dnd


#endif  // LAB3_CHARACTER_RACE_HPP_
