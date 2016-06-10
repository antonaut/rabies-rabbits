// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <string>
#include <vector>

namespace dnd {
    class Environment {
    protected:
        Environment() { }

    public:
        std::string name;
        std::string short_description;

        Environment(std::string env_name, std::string env_description) :
                name(env_name),
                short_description(env_description) { }
    };
}  // namespace dnd

#endif  // ENVIRONMENT_HPP
