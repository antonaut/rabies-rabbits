#ifndef LAB3_PLAYER_HPP_
#define LAB3_PLAYER_HPP_

#include <string>

namespace dnd {

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

}  // namespace dnd


#endif  // LAB3_PLAYER_HPP_
