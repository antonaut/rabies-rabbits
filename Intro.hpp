// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_INTRO_HPP_
#define LAB3_INTRO_HPP_

#include "GameObject.hpp"
#include "IntroComponent.hpp"
#include "EventBus.hpp"

namespace dnd {

struct Intro : public GameObject {
    Intro(EventBus *ebp):GameObject(ebp,
                                   {new IntroComponent(ebp)}) {}
};

}  // namespace dnd


#endif  // LAB3_INTRO_HPP_
