#ifndef LAB3_ITEM_HPP_
#define LAB3_ITEM_HPP_

#include <string>
#include "GameObject.hpp"

namespace lab3 {

    class Item : public GameObject {
        int weight;
        int damage;
        int defence;
        std::string name;

    public:
        explicit Item(int weight, std::string name, int damage = 0, int defence = 0) :
                GameObject(),
                weight(weight),
                damage(damage),
                defence(defence),
                name(name) { }

    };

}  // namespace lab3


#endif  // LAB3_ITEM_HPP_
