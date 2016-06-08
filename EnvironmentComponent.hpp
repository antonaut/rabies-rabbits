// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef ENVIRONMENT_COMPONENT_HPP
#define ENVIRONMENT_COMPONENT_HPP

#include <string>
#include <vector>

#include "Component.hpp"

namespace dnd
{
class EnvironmentComponent : public Component {
 private:
    std::string name;
    std::string short_description;
 protected:
    EnvironmentComponent() : Component(ComponentType::ENVIRONMENT) {}
 public:
    EnvironmentComponent(std::string env_name, std::string env_description) :
        Component(ComponentType::ENVIRONMENT),
        name(env_name),
        short_description(env_description) {}
};
}  // namespace dnd

#endif  // ENVIRONMENT_COMPONENT_HPP

