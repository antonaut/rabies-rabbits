//
// Created by aerholt on 2016-06-28.
//

#ifndef RABIESRABBIES_CROCSTOOTH_HPP_
#define RABIESRABBIES_CROCSTOOTH_HPP_

#include "Item.hpp"
namespace lab3 {
struct CrocsTooth: public Item {
  CrocsTooth(uint64_t owner_id) : Item("croc's tooth", owner_id, 40, 10, 0, true) { }
};
}

#endif //RABIESRABBIES_CROCSTOOTH_HPP_
