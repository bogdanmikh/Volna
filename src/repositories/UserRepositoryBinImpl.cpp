//
// Created by bogdan on 13.07.2023.
//

#pragma once

#include <cassert>
#include "UserRepositoryBinImpl.hpp"

#define path "../bin/Database.bin"
#define lenghtName 11
#define lenghtPassword 11

UserRepositoryBinImpl::UserRepositoryBinImpl() {
    read();
}

UserRepositoryBinImpl::~UserRepositoryBinImpl() {
    saveAll();
}

uint32_t UserRepositoryBinImpl::save(const User &item) {
    User userCopy = item;
    userCopy.id = ++lastId;
    data.emplace_back(userCopy);
    return lastId;
}

std::optional<User> UserRepositoryBinImpl::getById(uint32_t id) {
    if (id > lastId) return {};
    int32_t left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (data[mid].id == id) return data[mid];
        if (data[mid].id > id) right = mid - 1;
        else left = mid + 1;
    }
    return {};
}

void UserRepositoryBinImpl::update(uint32_t id, const User &item) {
    if (id > lastId) return;
    for (int i = 0; i < data.size() && data[i].id <= id; i++) {
        if (data[i].id == id) {
            data[i] = item;
            data[i].id = id;
            return;
        }
    }
}

void UserRepositoryBinImpl::deleteById(uint32_t id) {
    if (id > lastId) {
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

void UserRepositoryBinImpl::deleteAll() {
    std::ofstream clear(path, std::ios::out | std::ofstream::trunc);
    assert(clear.is_open());
    clear.close();
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
        lastId = 0;
        return;
    }
    dataInput.read(reinterpret_cast<char *>(&lastId), sizeof(uint32_t));
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
    deleteAll();
    openOut();
    uint32_t count = 0;
    if (!data.empty()) {
        count = data.size();
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
