cmake_minimum_required(VERSION 3.5.1)
project(rabiesrabbies)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(PROJECT_SOURCE_DIR)
set(HEADER_FILES
        Actor.hpp
        CharacterClass.hpp
        CharacterRace.hpp
        Crocodile.hpp
        Direction.hpp
        DungeonMap.hpp
        Environment.hpp
        GameObject.hpp
        Intro.hpp
        IOHelpers.hpp
        Item.hpp
        Player.hpp
        Rabbit.hpp
        REPL.hpp
        SmallForestMap.hpp
        Crocit.hpp)

set(SOURCE_FILES GameLoop.cpp)
set(TEST_SOURCE_FILES test.cpp tezt.hpp)

add_executable(rabiesrabbits ${SOURCE_FILES} ${HEADER_FILES})
add_executable(testexec ${TEST_SOURCE_FILES} ${HEADER_FILES})
