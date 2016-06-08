// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_EVENT_HPP
#define LAB3_EVENT_HPP

#include <string>

namespace dnd {

    struct Event {
    	std::string name;
    	void *data;
    	Event(std::string name, void *data=nullptr) :name(name), data(data) {}
        friend bool operator<(const Event &a, const Event &b) {
            return a.name < b.name;
        }
        virtual ~Event() {}
    };

    // *** Event documentation / API
    // This shows what the events should look like
    // and what we expect them to provide as args.

    // **** Const void events

    Event TEST_EVENT("TEST_EVENT");
    Event TESTARGS_EVENT("TESTARGS_EVENT", (void*) 42);
    Event FIXED_TICK_EVENT("FIXED_TICK_EVENT");

    Event EVT_GameObjectSpawned("GameObjectSpawned");
    Event EVT_GameObjectDestroyed("GameObjectDestroyed");
    Event EVT_Look("PlayerLook");
    Event EVT_Inventory("PlayerInventory");
    

    // **** Events with args


    // Target events

    // Will always have a struct like this as data

    struct target_evt {
        uint64_t src_id;
        std::string target_name;
    };

    Event *target_event(std::string event_name,
                        uint64_t id,
                        std::string target) {

        struct target_evt *evt_data = new target_evt{
            id,
            target
        };

        Event *ep = new Event(event_name, &evt_data);
        return ep;
    }

    // Events:
    // EVT_PlayerMove("PlayerMove", target_evt *);
    // EVT_PlayerFight("PlayerFight", target_evt *);
    // EVT_PlayerLoot("PlayerLoot", target_evt);
    // EVT_PlayerTalk("PlayerTalk", target_evt);

}  // namespace dnd

#endif  // LAB3_EVENT_HPP_
