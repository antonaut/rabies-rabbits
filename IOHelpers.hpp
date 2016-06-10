#ifndef LAB3_IOHELPERS_HPP_
#define LAB3_IOHELPERS_HPP_

#include <iostream>
#include <string>
#include <stdexcept>

namespace dnd {

    std::string get_string() {
        std::string line;
        if (!std::getline(std::cin, line)) {
            throw std::out_of_range("Ctrl-D");
        }
        return line;
    }

    int get_integer() {
        try {
            std::string line;
            if (!std::getline(std::cin, line)) {
                throw std::out_of_range("Ctrl-D");
            }
            int res = std::stoi(line, nullptr);
            return res;
        } catch (const std::invalid_argument &exception) {
            return 0;
        }
    }

}  // namespace dnd


#endif  // LAB3_IOHELPERS_HPP_
