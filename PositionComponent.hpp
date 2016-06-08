// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_POSITION_COMPONENT_HPP_
#define LAB3_POSITION_COMPONENT_HPP_

#include "Component.hpp"
#include "EnvironmentComponent.hpp"

namespace dnd {

    class PositionComponent : public Component {
    private:
    	EnvironmentComponent *location;
    public:
	    PositionComponent(EnvironmentComponent *location) : Component(ComponentType::POSITION), location(location) {}
    	virtual ~PositionComponent();
    };


}  // namespace dnd

#endif  // LAB3_POSITION_COMPONENT_HPP_
