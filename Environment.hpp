// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>
#include <vector>

#include "GameObject.hpp"

namespace lab3 {

    typedef const int EnvironmentType;

    EnvironmentType FOREST_TYPE = 1;
    EnvironmentType SWAMP_TYPE = 2;
    EnvironmentType MOUNTAIN_TYPE = 3;

    class Environment : public GameObject {
    protected:
        Environment() = delete;
    public:
        std::string name;
        std::string short_description;
        EnvironmentType type;

        Environment(EnvironmentType type, std::string env_name, std::string env_description) :
                name(env_name),
                short_description(env_description),
                type(type) { }

    };


}  // namespace lab3


#endif  // ENVIRONMENT_HPP
