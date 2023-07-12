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

int UserRepository::addUser(std::string name, std::string password) {
    int lastId = getLastId() + 1;
    openOut();
    if (lastId == 1) {
        dataOutput << lastId << '~' << name << '~' << password;
    } else {
        dataOutput << std::endl << lastId << '~' << name << '~' << password;
    }
    dataOutput.close();
    return lastId;
}

void UserRepository::updateName(int id, std::string newName) {
    int size = getLastId();
    if (!findUser(id)) {
        std::cout << "User not found\n";
        return;
    }
    std::vector<std::string> str = getAllLines();
    std::string infoUser = str[id - 1];
    int countSym = 0;
    int startName = 0;
    int endName = 0;
    for (int i = 0; countSym != 2; i++) {
        if (infoUser[i] == '~') {
            countSym++;
            if (countSym == 1) {
                startName = i + 1;
                continue;
            }
        }
        if (countSym == 2) endName = i - 1;
    }
    std::string updatingInfo;
    for (int i = 0; i < infoUser.size(); i++) {
        if (i == startName) {
            i = endName;
            updatingInfo += newName;
            continue;
        }
        updatingInfo.push_back(infoUser[i]);
    }
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    for (int i = 0; i < size - 1; i++) {
        if (i + 1 == id) {
            dataOutput << updatingInfo << std::endl;
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    dataOutput << str[size - 1];
    dataOutput.close();
}

void UserRepository::updatePassword(int id, std::string password) {
    int size = getLastId();
    if (!findUser(id)) {
        std::cout << "User not found\n";
        return;
    }
    std::vector<std::string> str = getAllLines();
    std::string infoUser = str[id - 1];
    int sizePassword = 0;
    for (int i = infoUser.size() - 1; infoUser[i] != '~'; i--) {
        sizePassword++;
    }
    std::string updatingInfo;
    int countSym = 0;
    for (int i = 0; i < infoUser.size(); i++) {
        if (infoUser[i] == '~') countSym++;
        updatingInfo.push_back(infoUser[i]);
        if (countSym == 2) {
            updatingInfo += password;
            break;
        }
    }
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    for (int i = 0; i < size - 1; i++) {
        if (i + 1 == id) {
            dataOutput << updatingInfo << std::endl;
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    dataOutput << str[size - 1];
    dataOutput.close();
}

void UserRepository::getInfoUser(int id) {
    if (!findUser(id)) {
        std::cout << "User not found\n";
        return;
    }
    std::string infoUser;
    openIn();
    std::getline(dataInput, infoUser);
    for (int i = 1; getId(infoUser) != id; i++) {
        std::getline(dataInput, infoUser);
    }
    dataInput.close();
    std::cout << getInfo(infoUser) << std::endl;
}

void UserRepository::deleteUser(int id) {
    int size = getLastId();
    if (!findUser(id)) {
        std::cout << "User not found\n";
        return;
    }
    std::vector<std::string> str = getAllLines();
    std::ofstream clearFile(path, std::ios::out);
    clearFile.close();
    openOut();
    for (int i = 0; i < size - 1; i++) {
        if (i + 1 == id) {
            continue;
        }
        dataOutput << str[i] << std::endl;
    }
    dataOutput << str[size - 1];
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

std::vector<std::string> UserRepository::getAllLines() {
    int size = getLastId();
    std::vector<std::string> vecStr(size);
    openIn();
    for (int i = 0; i < size; i++) {
        std::getline(dataInput, vecStr[i]);
    }
    dataInput.close();
    return vecStr;
}

std::string UserRepository::getInfo(std::string info) {
    std::string resultInfo;
    resultInfo = "Id: ";
    bool k = true;
    for (int i = 0; i < info.size(); i++) {
        if (info[i] == '~') {
            if (k) {
                resultInfo += " Name: ";
                k = false;
            } else {
                resultInfo += " Password: ";
            }
            continue;
        }
        resultInfo.push_back(info[i]);
    }
    return resultInfo;
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

bool UserRepository::findUser(int id) {
    if (id > getLastId()) {
        return false;
    }
    std::string str;
    openIn();
    std::getline(dataInput, str);
    while (getId(str) <= id) {
        if (getId(str) == id) {
            dataInput.close();
            return true;
        }
        std::getline(dataInput, str);
    }
    dataInput.close();
    return false;
}

int UserRepository::getId(std::string infoUser) {
    std::string id;
    for (int i = 0; infoUser[i] != '~'; i++) {
        id.push_back(infoUser[i]);
    }
    return std::stoi(infoUser);
}
