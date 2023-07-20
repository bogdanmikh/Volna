#pragma once

#include <fstream>
#include <cassert>
#include <string>

#include "UserRepository.hpp"

// Create
// Read
// Update
// Delete

class UserRepositoryCsvImpl final: public UserRepository {
public:
    ~UserRepositoryCsvImpl() override;
    uint32_t save(const User &user) override;
    std::optional<User> getById(uint32_t id) override;
    void update(uint32_t id, const User &user) override;
    void deleteById(uint32_t id) override;
    std::vector<User> getAll() override;
private:
    std::ifstream dataInput;
    std::ofstream dataOutput;

    void openIn() ;
    void openOut();
    std::vector<std::string> getLines();
    uint32_t getLastId();
    User getUser(std::string info);
    uint32_t getId(std::string infoUser);
    int32_t count();
};