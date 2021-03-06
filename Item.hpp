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

  bool isDecayed() const {
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
  void setTicksUntilDecay(int ticksUntilDecay);

  friend
  std::ostream& operator<<(std::ostream& str, const Item &item) {
    str << "[" << item.id << "] - " << item.name << "("
        << "W:" << item.weight << ", "
        << "Dmg:" << item.damage << ", "
        << "Def:" << item.defence << ")";

    return str;
  }
};

/**
 * @return std::vector<Item *> inv - the getInventory of the GameObject with id 'id'.
 **/
std::vector<Item *> *getInventory(const uint64_t id);

/**
 * Performs 'action' on the item with id 'item_id'.
 **/
void itemAction(uint64_t item_id, std::function<void(uint64_t, Item *)> action);

void inventory_insert(const uint64_t to, Item *item);

/**
 * Holds all Items in the game.
 */
std::vector<Item *> ITEMS;

Item::Item(std::string name, uint64_t owner_id, int weight, int damage, int defence, bool decayable) :
    GameObject(),
    weight(weight),
    damage(damage),
    defence(defence),
    name(name),
    decayable(decayable),
    hasDecayed(false),
    ticksUntilDecay(20) {
  ITEMS.push_back(this);
  inventory_insert(owner_id, this);
  std::clog << "Item spawned: " << this << std::endl;
}

Item::~Item() {
  for (auto it = ITEMS.begin(); it != ITEMS.end(); ++it) {
    if (*it == this) {
      ITEMS.erase(it);
      return;
    }
  }
}

void Item::setTicksUntilDecay(int ticksUntilDecay) {
  this->ticksUntilDecay = ticksUntilDecay;
}


// theVoid holds Items which are to be removed from the game.
GameObject *theVoid = new GameObject();

// INVENTORIES holds the ITEMS for all the game objects
std::map<uint64_t, std::vector<Item *>> INVENTORIES;

void inventory_insert(const uint64_t to, Item *item) {
  auto it = INVENTORIES.find(to);
  if (it == INVENTORIES.end()) {
    INVENTORIES.insert(std::make_pair(to, std::vector<Item *>(0)));
    it = INVENTORIES.find(to);
  }
  it->second.push_back(item);
}

bool item_transfer(const uint64_t item_id, const uint64_t from, const uint64_t to) {
  for (auto it = INVENTORIES[from].begin(); it != INVENTORIES[from].end(); ++it) {
    auto ip = *it;
    if (ip->id == item_id) {
      INVENTORIES[from].erase(it);
      inventory_insert(to, ip);
      return true;
    }
  }
  return false;
}

std::vector<Item *> empty;

std::vector<Item *> *getInventory(const uint64_t id) {
  try {
    return &INVENTORIES.at(id);
  } catch (const std::out_of_range &ex) {
    return &empty;
  }
}

void itemAction(uint64_t item_id, std::function<void(uint64_t, Item *)> action) {
  for (auto it = INVENTORIES.begin(); it != INVENTORIES.end(); ++it) {
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
    item_transfer(item_id, owner_id, theVoid->id);
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
  for (auto it = ITEMS.begin(); it != ITEMS.end(); ++it) {
    if ((*it)->id == id) {
      return *it;
    }
  }

  throw std::invalid_argument("No such item found");
}

/**
 * If more than one Item with a matching name is found, this only returns the first one.
 * Returns null if no items are found.
 */
Item *findItemByNameInInventory(std::string name, const uint64_t inventory_id) {
  for (auto &item: INVENTORIES[inventory_id]) {
    std::string item_name_prefix = item->getName().substr(0, item->getName().find(' '));
    if (item_name_prefix.compare(name)== 0) {
      return item;
    }
  }
  return nullptr;
}

}  // namespace lab3


#endif  // LAB3_ITEM_HPP_
