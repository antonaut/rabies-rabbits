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

    class EventBus {
    private:
        std::map<std::string, std::vector<std::function<void()>>> event_map;

        void log_evt(const std::string &prefix, Event *evt) {
            std::cerr << prefix << evt->name;
            if (evt->data != nullptr) {
                std::cerr << " - " << evt->data;
            }
            std::cerr << std::endl;
        }

    public:
        EventBus() { }

        ~EventBus() { }

        EventBus(const EventBus &eb) = delete;

        EventBus(EventBus &&eb) = delete;

        EventBus &operator=(const EventBus &eb) = delete;

        EventBus &operator=(EventBus &&eb) = delete;

        template<class F, class... Args>
        void add_event_listener(std::string event_name, F fn, Args &&... args) {
            auto it = event_map.find(event_name);

            std::function<void()> callback = std::bind(fn, args...);

            if (it == event_map.end()) {                // Not found
                (void) event_map.insert(std::make_pair(event_name, std::vector<std::function<void()>>(0)));
                it = event_map.find(event_name);
            }

            (*it).second.push_back(callback);
        }

        // Does nothing if no listeners are registered.

        void fire(Event *evt) {
            auto it = event_map.find(evt->name);

            this->log_evt("DEBUG: ", evt);

            if (it == event_map.end()) {
                return;
            }


            for (auto callback : (*it).second) {
                callback();
            }
            delete evt;
        }
    };
}  // namespace dnd

#endif  // LAB3_EVENT_BUS_HPP_
