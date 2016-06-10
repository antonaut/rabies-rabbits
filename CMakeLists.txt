cmake_minimum_required(VERSION 3.5.1)
project(rabiesrabbies)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(PROJECT_SOURCE_DIR)
set(SOURCE_FILES GameLoop.cpp
        Actor.hpp
        CharacterClass.hpp
        CharacterRace.hpp
        Crocodile.hpp
        Direction.hpp
        DungeonMap.hpp
        Environment.hpp
        Event.hpp
        EventBus.hpp
        GameObject.hpp
        Intro.hpp
        IOHelpers.hpp
        Item.hpp
        Player.hpp
        Rabbit.hpp
        REPL.hpp
        SmallForestMap.hpp)

add_executable(rabiesrabbits ${SOURCE_FILES})
