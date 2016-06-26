// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_INVENTORY_HPP
#define LAB3_INVENTORY_HPP

#include "GameObject.hpp"
#include "Item.hpp"

namespace lab3 {

std::map<uint64_t, std::vector<Item *>> inventories;

bool item_transfer(const uint64_t item_id, const uint64_t from, const uint64_t to) {
  for (auto it = inventories[from].begin(); it != inventories[from].end(); ++it) {
    auto ip = *it;
    if (ip->id == item_id) {
      inventories[from].erase(it);
      auto it = inventories.find(to);
      if (it == inventories.end()) {
        inventories.insert(std::make_pair(to, std::vector<Item *>(0)));
        it = inventories.find(to);
      }
      it->second.push_back(ip);
      return true;
    }
  }
  return false;
}

std::vector<Item *> &inventory(const uint64_t id) {
  return inventories[id];
}

}


#endif // LAB3_INVENTORY_HPP
