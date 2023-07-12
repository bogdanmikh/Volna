//
// Created by bogdan on 11.07.2023.
//

#include <cstdint>
#include <iostream>

struct User final {
    uint32_t id;
    std::string name;
    std::string password;

    User(uint32_t id, const std::string &name, const std::string &password)
            : id(id)
            , name(name)
            , password(password) {}

    User(const std::string &name, const std::string &password)
            : id(0)
            , name(name)
            , password(password) {}
};
