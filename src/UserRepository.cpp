#pragma once

#include <cassert>
#include <string>
#include "UserRepository.hpp"

#define path "../Database.csv"

UserRepository::~UserRepository() {
    if (dataInput.is_open()) {
        dataInput.close();
    }
    if (dataOutput.is_open()) {
        dataOutput.close();
    }
}

int UserRepository::addUser(const User &user) {
    int lastId = getLastId() + 1;
    openOut();
    if (lastId == 1) {
        dataOutput << lastId << '~' << user.name << '~' << user.password;
    } else {
        dataOutput << std::endl << lastId << '~' << user.name << '~' << user.password;
    }
    dataOutput.close();
    return lastId;
}

std::string UserRepository::getUser(const int &id) {
    std::string str;
    openIn();
    while (dataInput) {
        std::getline(dataInput, str);
        if (getId(str) == id) {
            dataInput.close();
            return str;
        }
    }
    dataInput.close();
    return "-1";
}

void UserRepository::update(const User &user, int id) {
    std::string infoUser = getUser(id);
    if (infoUser == "-1") {
        std::cout << "User not found\n";
        return;
    }
    std::string updatingInfo = std::to_string(id)  + "~" + user.name + "~" + user.password;
    int size = count();
    std::vector<std::string> str = getLines();
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    for (int i = 0; i < size - 1; i++) {
        if (getId(str[i]) == id) {
            dataOutput << updatingInfo << std::endl;
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    if (size == id) {
        dataOutput << updatingInfo;
    } else {
        dataOutput << str[size - 1];
    }
    dataOutput.close();
}

void UserRepository::deleteUser(int id) {
    std::string infoUser = getUser(id);
    if (infoUser == "-1") {
        std::cout << "User not found\n";
        return;
    }
    int size = count();
    std::vector<std::string> str = getLines();
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    for (int i = 0; i < size - 1; i++) {
        if (getId(str[i]) == id) {
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    if (getId(str[size - 1]) != id) {
        dataOutput << str[size - 1];
    }
    dataOutput.close();
}

void UserRepository::openIn() {
    dataInput.open(path);
    assert(dataInput.is_open());
}

void UserRepository::openOut() {
    dataOutput.open(path, std::ofstream::app);
    assert(dataOutput.is_open());
}

std::vector<std::string> UserRepository::getLines() {
    std::vector<std::string> vecStr;
    openIn();
    for (int i = 0; dataInput; i++) {
        std::string str;
        std::getline(dataInput, str);
        if (!str.empty()) {
            vecStr.push_back(str);
        }
    }
    dataInput.close();
    return vecStr;
}

int UserRepository::getLastId() {
    openIn();
    std::string lastLine;
    while (dataInput) {
        std::getline(dataInput, lastLine);
    }
    dataInput.close();
    if (lastLine.empty()) {
        return 0;
    }
    std::string id;
    for (int i = 0; lastLine[i] != '~'; i++) {
        id.push_back(lastLine[i]);
    }
    return std::stoi(id);
}

std::string UserRepository::getPassword(int id) {
    if (id >= getLastId()) {
        return "-1";
    }
    std::string infoUser;
    openIn();
    for (int i = 1; i <= id; i++) {
        std::getline(dataInput, infoUser);
    }
    dataInput.close();
    std::string passwordUser;
    for (int i = infoUser.size(); infoUser[i] != '~'; i--) {
        passwordUser.push_back(infoUser[i]);
    }
    std::reverse(passwordUser.begin(), passwordUser.end());
    return passwordUser;
}

int UserRepository::getId(std::string infoUser) {
    std::string id;
    for (int i = 0; infoUser[i] != '~'; i++) {
        id.push_back(infoUser[i]);
    }
    return std::stoi(infoUser);
}

int UserRepository::count() {
    int i = 0;
    std::string str;
    openIn();
    while (std::getline(dataInput, str)) {
        i++;
    }
    dataInput.close();
    return i;
}