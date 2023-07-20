//
// Created by bogdan on 13.07.2023.
//

#pragma once

#include <cassert>
#include "UserRepositoryBinImpl.hpp"

#define path "../bin/Database.bin"
#define lenghtName 7
#define lenghtPassword 7

UserRepositoryBinImpl::UserRepositoryBinImpl() {
    read();
}

UserRepositoryBinImpl::~UserRepositoryBinImpl() {
    saveAll();
}

uint32_t UserRepositoryBinImpl::save(const User &item) {
    User userCopy = item;
    uint32_t lastId = 1;
    if (!data.empty()) {
        lastId = data[data.size() - 1].id + 1;
    }
    userCopy.id = lastId;
    data.emplace_back(userCopy);
    return lastId;
}

std::optional<User> UserRepositoryBinImpl::getById(uint32_t id) {
    if (id > data[data.size() - 1].id) return {};
    for (int i = 0; i < data.size() && data[i].id <= id; i++) {
        if (data[i].id == id) return data[i];
    }
    return {};
}

void UserRepositoryBinImpl::update(uint32_t id, const User &item) {
    if (id > data[data.size() - 1].id) return;
    for (int i = 0; i < data.size() && data[i].id < id; i++) {
        if (data[i].id == id) {
            data[i] = item;
            data[i].id = id;
            return;
        }
    }
}

void UserRepositoryBinImpl::deleteById(uint32_t id) {
    if (id > data[data.size() - 1].id) {
        return;
    }
    for (int i = 0; i < data.size(); i++) {
        if (data[i].id == id) {
            data.erase(data.begin() + i);
            return;
        }
    }
}

std::vector<User> UserRepositoryBinImpl::getAll() {
    return data;
}

void UserRepositoryBinImpl::openIn() {
    dataInput.open(path);
    assert(dataInput.is_open());
}

void UserRepositoryBinImpl::openOut() {
    dataOutput.open(path, std::ios::trunc);
    assert(dataOutput.is_open());
}

void UserRepositoryBinImpl::read() {
    openIn();
    uint32_t count;
    if (!dataInput.read(reinterpret_cast<char *>(&count), sizeof(uint32_t))) {
        dataInput.close();
        return;
    }
    dataInput.seekg(8);
    for (int i = 0; i < count; i++) {
        uint32_t id;
        dataInput.read(reinterpret_cast<char *>(&id), 4);
        char name[lenghtName];
        dataInput.read(name, lenghtName);
        char password[lenghtPassword];
        dataInput.read(password, lenghtPassword);
        data.emplace_back(id, name, password);
    }

    dataInput.close();
}


void UserRepositoryBinImpl::saveAll() {
    std::ofstream clear(path, std::ios::out);
    assert(clear.is_open());
    clear.close();
    openOut();
    uint32_t count = 0;
    uint32_t lastId = 0;
    if (!data.empty()) {
        count = data.size();
        lastId = data[data.size() - 1].id;
    }
    dataOutput.write(reinterpret_cast<const char *>(&count), 4);
    dataOutput.write(reinterpret_cast<const char *>(&lastId), 4);
    if (data.empty()) {
        dataOutput.close();
        return;
    }
    for (int i = 0; i < data.size(); i++) {
        User& user = data[i];
        dataOutput.write(reinterpret_cast<const char *>(&user.id), 4);
        dataOutput.write(user.name.c_str(), lenghtName);
        dataOutput.write(user.password.c_str(), lenghtPassword);
    }
    dataOutput.close();
}
