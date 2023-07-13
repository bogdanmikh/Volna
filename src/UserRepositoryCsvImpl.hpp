#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "model/User.hpp"
#include "CrudRepository.hpp"

// Create
// Read
// Update
// Delete

class UserRepositoryCsvImpl final: public CrudRepository<User, int> {
public:
    ~UserRepositoryCsvImpl();
    int save(const User &user) override;
    std::optional<User> getById(int id) override;
    void update(int id, const User &user) override;
    void deleteById(int id) override;
    std::vector<User> getAll() override;
private:
    std::ifstream dataInput;
    std::ofstream dataOutput;

    void openIn() ;
    void openOut();
    std::vector<std::string> getLines();
    int getLastId();
    User getUser(std::string info);
    int getId(std::string infoUser);
    int count();
};