// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_RACE_HPP_
#define LAB3_RACE_HPP_

#include <string>
#include <vector>

namespace lab3 {

struct Race {
  std::string name;
  std::string sound;

  friend std::ostream &operator<<(std::ostream &str, const Race c);

  std::string noise() const {
    return this->sound;
  }
};

std::ostream &operator<<(std::ostream &str, const Race c) {
  str << c.name;
  return str;
}

std::vector<Race> character_races = {
    Race{"Bear", "RAAWR!"},
    Race{"Fox", "Grrrr..."},
    Race{"Wolf", "GRROWL!"},
};

const Race RACE_RABBIT{"Rabbit", "Omnomnom."};
const Race RACE_CROCODILE{"Crocodile", "Snap-snap!"};
const Race RACE_RABBIDILE{"Rabbidile", "Omnom-snap-nom!"};

}  // namespace lab3


#endif  // LAB3_RACE_HPP_
