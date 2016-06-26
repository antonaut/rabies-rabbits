#ifndef LAB3_ITEM_HPP_
#define LAB3_ITEM_HPP_

#include <string>
#include "GameObject.hpp"
#include "TickCount.hpp"

namespace lab3 {


/**
 * The memory life cycle for this class is as follows.
 *
 * Construction
 **/


/**
 * Transfers an item from one GameObject to another.
 * @param uint64_t item_id - the id of the item
 * @param uint64_t from - the id of the GameObject to transfer from
 * @param uint64_t to - the id of the GameObject to transfer to
 * @return true  - if item was transferred
 *         false - otherwise
 **/
bool item_transfer(const uint64_t item_id, const uint64_t from, const uint64_t to);

/**
 * Moves the Item with id 'item_id' to the void GameObject for deletion/removal
 * from the game.
 **/
void moveToVoid(uint64_t item_id);

uint64_t getOwnerId(uint64_t item_id);


class Item: public GameObject {
  int weight;
  int damage;
  int defence;
  std::string name;
  bool decayable, hasDecayed;
  int ticksUntilDecay;

 public:
  explicit Item(std::string name, uint64_t owner_id, int weight, int damage, int defence, bool decayable);


  virtual ~Item();

  virtual void action() override {
    if (this->decayable) {
      if (this->tickHasChangedSinceLastAction()) {
        --ticksUntilDecay;
      }

      if (ticksUntilDecay <= 0) {
        this->hasDecayed = true;
      }
    }

    GameObject::action();
  }

  bool isDecayed() {
    return this->hasDecayed;
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
};

/**
 * @return std::vector<Item *> inv - the inventory of the GameObject with id 'id'.
 **/
std::vector<Item *> &inventory(const uint64_t id);

/**
 * Performs 'action' on the item with id 'item_id'.
 **/
void itemAction(uint64_t item_id, std::function<void(uint64_t, Item *)> action);

void inventory_insert(const uint64_t to, Item *item);

std::vector<Item *> items;

Item::Item(std::string name, uint64_t owner_id, int weight, int damage, int defence, bool decayable) :
    GameObject(),
    weight(weight),
    damage(damage),
    defence(defence),
    name(name),
    decayable(decayable),
    hasDecayed(false),
    ticksUntilDecay(20) {
  items.push_back(this);
  inventory_insert(owner_id, this);
}

Item::~Item() {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if (*it == this) {
      items.erase(it);
      return;
    }
  }
}


// theVoid holds Items which are to be removed from the game.
GameObject theVoid;

// inventories holds the items for all the game objects
std::map<uint64_t, std::vector<Item *>> inventories;

void inventory_insert(const uint64_t to, Item *item) {
  auto it = inventories.find(to);
  if (it == inventories.end()) {
    inventories.insert(std::make_pair(to, std::vector<Item *>(0)));
    it = inventories.find(to);
  }
  it->second.push_back(item);
}

bool item_transfer(const uint64_t item_id, const uint64_t from, const uint64_t to) {
  for (auto it = inventories[from].begin(); it != inventories[from].end(); ++it) {
    auto ip = *it;
    if (ip->id == item_id) {
      inventories[from].erase(it);
      inventory_insert(to, ip);
      return true;
    }
  }
  return false;
}


std::vector<Item *> &inventory(const uint64_t id) {
  return inventories[id];
}

void itemAction(uint64_t item_id, std::function<void(uint64_t, Item *)> action) {
  for (auto it = inventories.begin(); it != inventories.end(); ++it) {
    auto ownerItemPair = *it;
    for (auto jt = ownerItemPair.second.begin(); jt != ownerItemPair.second.end(); ++jt) {
      auto itemPointer = *jt;
      if (itemPointer->id == item_id) {
        action(ownerItemPair.first, itemPointer);
        return;
      }
    }
  }
}

void moveToVoid(uint64_t item_id) {
  itemAction(item_id, [&](uint64_t owner_id, Item *item) {
    item_transfer(item_id, owner_id, theVoid.id);
  });
}

uint64_t getOwnerId(uint64_t item_id) {
  uint64_t owner_id;
  itemAction(item_id, [&owner_id](uint64_t o_id, Item *item) {
    owner_id = o_id;
  });
  return owner_id;
}


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
