#ifndef LAB3_ITEM_HPP_
#define LAB3_ITEM_HPP_

#include <string>
#include "GameObject.hpp"

namespace lab3 {


class Item;

std::vector<Item *> items;

class Item: public GameObject {
  int weight;
  int damage;
  int defence;
  std::string name;

 public:
  explicit Item(uint64_t owner_id, int weight, std::string name, int damage = 0, int defence = 0) :
      GameObject(),
      weight(weight),
      damage(damage),
      defence(defence),
      name(name) {
    items.push_back(this);
  }


  int getDamage() const {
    return damage;
  }


  const std::string &getName() const {
    return name;
  }

  int getWeight() const {
    return weight;
  }

  int getDefence() const {
    return defence;
  }

  virtual ~Item() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      if (*it == this) {
        items.erase(it);
        return;
      }
    }
  }
};


Item *findItemById(uint64_t id) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if ((*it)->id == id) {
      return *it;
    }
  }

  throw std::invalid_argument("No such item found");
}

}  // namespace lab3


#endif  // LAB3_ITEM_HPP_
