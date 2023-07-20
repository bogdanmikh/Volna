#pragma once

#include "UserRepositoryCsvImpl.hpp"

#define path "../bin/Database.csv"

UserRepositoryCsvImpl::~UserRepositoryCsvImpl() {
    if (dataInput.is_open()) {
        dataInput.close();
    }
    if (dataOutput.is_open()) {
        dataOutput.close();
    }
}

uint32_t UserRepositoryCsvImpl::save(const User &user) {
    uint32_t lastId = getLastId() + 1;
    openOut();
    if (lastId == 1) {
        dataOutput << lastId << '~' << user.name << '~' << user.password;
    } else {
        dataOutput << std::endl << lastId << '~' << user.name << '~' << user.password;
    }
    dataOutput.close();
    return lastId;
}

std::optional<User> UserRepositoryCsvImpl::getById(uint32_t id) {
    openIn();
    std::string str;
    while (dataInput) {
        std::getline(dataInput, str);
        if (str.empty()) break;
        if (getId(str) == id) {
            dataInput.close();
            std::string name, password;
            int l = 0;
            for (int i = 0; i < str.size(); i++) {
                if (str[i] == '~') {
                    l++;
                    continue;
                }
                if (l == 1) name.push_back(str[i]);
                else if (l == 2) password.push_back(str[i]);
            }
            User user(id, name, password);
            return user;
        }
    }
    dataInput.close();
    return {};
}

void UserRepositoryCsvImpl::update(uint32_t id, const User &user) {
    std::optional<User> infoUser = getById(id);
    if (!infoUser) {
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
    if (getId(str[size - 1]) == id) {
        dataOutput << updatingInfo;
    } else {
        dataOutput << str[size - 1];
    }
    dataOutput.close();
}

void UserRepositoryCsvImpl::deleteById(uint32_t id) {
    std::optional<User> infoUser = getById(id);
    if (!infoUser) {
        std::cout << "User not found\n";
        return;
    }
    int size = count();
    std::vector<std::string> str = getLines();
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    if (size == 1) {
        dataOutput.close();
        return;
    } else if (size == 2) {
        if (id == 1) dataOutput << str[1];
        else dataOutput << str[0];
        dataOutput.close();
        return;
    }

    for (int i = 0; i < size - 2; i++) {
        if (getId(str[i]) == id) {
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    dataOutput << str[size - 2];
    if (getId(str[size - 1]) != id) {
        dataOutput << std::endl << str[size - 1];
    }
    dataOutput.close();
}

std::vector<User> UserRepositoryCsvImpl::getAll() {
    std::vector<User> allUsers;
    std::string str;
    openIn();
    while (dataInput) {
        dataInput >> str;
        allUsers.push_back(getUser(str));
    }
    dataInput.close();
    return allUsers;
}


void UserRepositoryCsvImpl::openIn() {
    dataInput.open(path);
    assert(dataInput.is_open());
}

void UserRepositoryCsvImpl::openOut() {
    dataOutput.open(path, std::ofstream::app);
    assert(dataOutput.is_open());
}

std::vector<std::string> UserRepositoryCsvImpl::getLines() {
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

uint32_t UserRepositoryCsvImpl::getLastId() {
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
    return static_cast<uint32_t>(std::stoi(id));
}

User UserRepositoryCsvImpl::getUser(std::string info) {
    std::string id, name, password;
    int k = 0;
    for (char i : info) {
        if (i == '~') {
            k++;
            continue;
        }
        if (k == 0) {
            id.push_back(i);
        } else if (k == 1) {
            name.push_back(i);
        } else if (k == 2) {
            password.push_back(i);
        }
    }
    return {static_cast<uint32_t>(std::stoi(id)), name, password};
}

uint32_t UserRepositoryCsvImpl::getId(std::string infoUser) {
    std::string id;
    for (int i = 0; infoUser[i] != '~'; i++) {
        id.push_back(infoUser[i]);
    }
    return static_cast<uint32_t>(std::stoi(id));
}

int UserRepositoryCsvImpl::count() {
    int i = 0;
    std::string str;
    openIn();
    while (std::getline(dataInput, str)) {
        i++;
    }
    dataInput.close();
    return i;
}