#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <string>

namespace lab3 {

    class Item {
        int weight;
        int damage;
        int defence;
        std::string name;

    public:
        explicit Item(int weight, std::string name, int damage = 0, int defence = 0) :
                weight(weight),
                damage(damage),
                defence(defence),
                name(name) { }

    };

}  // namespace lab3


#endif  // LAB3_PLAYER_HPP_
