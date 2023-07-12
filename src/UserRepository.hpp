#pragma once

#include <iostream>
#include <fstream>
#include <vector>

// Create
// Read
// Update
// Delete

class UserRepository final {
public:
    ~UserRepository();
    int addUser(std::string name, std::string password);
    void updateName(int id, std::string newName);
    void updatePassword(int id, std::string password);
    void getInfoUser(int id);
    void deleteUser(int id);
private:
    std::ifstream dataInput;
    std::ofstream dataOutput;

    void openIn() ;
    void openOut();
    std::vector<std::string> getAllLines();
    std::string getInfo(std::string info);
    int getLastId();
    std::string getPassword(int id);
    bool findUser(int id);
    int getId(std::string infoUser);
};