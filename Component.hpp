// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_COMPONENT_HPP_
#define LAB3_COMPONENT_HPP_

namespace dnd {

enum ComponentType {
    INTRO,
    POSITION,
    MOVEMENT,
    REPL,
    ENVIRONMENT,
    EXIT,
    DUNGEON_MAP,
    MAXIMUM_MOB,
    HEALTH,
    PLAYER,
    EXPERIENCE,
    TALKING,
    FIGHTING,
    EQUIPMENT,
    ANNOUNCE,
    RABBIT_SPAWNER,
    RABBIT_AI
};

class Component {
 protected:
    Component() = delete;
    ComponentType type;
 public:
    explicit Component(ComponentType type) : type(type) {}
    virtual ~Component() {}

    // TODO(antonaut) Think about these...
    Component(const Component &) = delete;
    Component(Component &&) = delete;
    Component& operator=(const Component&) = delete;
    Component& operator=(Component&&) = delete;

    ComponentType get_type(void) { return this->type; }

    // Optional to override these
    virtual void setup() {}
    virtual void update(double delta) {(void)delta;}
    virtual void fixed_update() {}
};
}  // namespace dnd

#endif  // LAB3_COMPONENT_HPP_
