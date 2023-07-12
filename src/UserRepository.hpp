#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "model/User.hpp"

// Create
// Read
// Update
// Delete

class UserRepository final {
public:
    ~UserRepository();
    int addUser(const User &user);
    std::string getUser(const int &id);
    void update(const User &user, int id);
    void deleteUser(int id);
private:
    std::ifstream dataInput;
    std::ofstream dataOutput;

    void openIn() ;
    void openOut();
    std::vector<std::string> getLines();
    int getLastId();
    std::string getPassword(int id);
    bool findUser(int id);
    int getId(std::string infoUser);
    int count();
};