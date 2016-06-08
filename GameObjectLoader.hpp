// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef GAME_OBJECT_LOADER_HPP
#define GAME_OBJECT_LOADER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "GameObject.hpp"

namespace dnd {
    class GameObjectLoader
    {
        std::shared_ptr< std::vector<GameObject> > load(std::string filename) {
            std::clog << "Loaded " << filename << std::endl;
            auto gobs = std::make_shared< std::vector<GameObject> >(0);
            return gobs;
        }
    };
}  // namespace dnd

#endif  // GAME_OBJECT_LOADER_HPP
