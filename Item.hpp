#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <string>

namespace dnd {

    class Item {
        int weight;
        std::string name;
        Item = 0;

    public:
        Item(int weight, std::string name) :
                weight(weight),
                name(name) { }

    };

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
