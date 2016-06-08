// Copyright 2016 Anton Erholt <aerholt@kth.se>

#ifndef LAB3_EVENT_BUS_HPP_
#define LAB3_EVENT_BUS_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>

#include "Event.hpp"

namespace dnd {

typedef std::function<void(Event*)> EventListener;

class EventBus {
 private:
    std::map<Event, std::vector<EventListener>> event_map;

    void log_evt(const std::string &prefix, Event *evt) {
        std::cerr << prefix << evt->name;
        if (evt->data != nullptr) {
            std::cerr << " - " << evt->data;
        }
        std::cerr << std::endl;
    }

 public:
    EventBus() {}
    ~EventBus() {}
    EventBus(const EventBus &eb) = delete;
    EventBus(EventBus &&eb) = delete;
    EventBus& operator=(const EventBus& eb) = delete;
    EventBus& operator=(EventBus &&eb) = delete;

    void add_event_listener(Event event_name, EventListener callback) {
        auto it = event_map.find(event_name);

        if (it == event_map.end()) {                // Not found
            (void) event_map.insert (std::make_pair(event_name, std::vector<EventListener>(0)));
            it = event_map.find(event_name);
        }

        (*it).second.push_back(callback);
    }

    // Does nothing if no listeners are registered.
    
    void fire(Event * evt) {
        auto it = event_map.find(evt->name);
        this->log_evt("DEBUG: ", evt);
        if (it == event_map.end()) {
            return;
        }


        for (auto callback : (*it).second) {
            callback(evt);
        }
    }
};
}  // namespace dnd

#endif  // LAB3_EVENT_BUS_HPP_
