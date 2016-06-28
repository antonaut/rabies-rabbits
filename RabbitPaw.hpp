//
// Created by aerholt on 2016-06-28.
//

#ifndef RABIESRABBIES_RABBITPAW_HPP_
#define RABIESRABBIES_RABBITPAW_HPP_

#include "Item.hpp"
namespace lab3 {

struct RabbitPaw: public Item {
  RabbitPaw(uint64_t owner_id) :
      Item("rabbit paw", owner_id, 20, 0, 10, true) { }
};

}

#endif //RABIESRABBIES_RABBITPAW_HPP_
