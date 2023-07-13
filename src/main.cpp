#include "UserRepositoryCsvImpl.hpp"
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include "CrudRepository.hpp"

User generateUser() {
    std::string name;
    std::string password;
    std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < 7; i++) {
        int _rand = std::rand() % 100;
        if (_rand > 62) _rand = 100 - _rand;
        name.push_back(str[_rand]);
    }
    for (int i = 0; i < 10; i++) {
        int _rand = std::rand() % 100;
        if (_rand > 62) _rand = 100 - _rand;
        password.push_back(str[_rand]);
    }
    User result(name, password);
    return result;
}

int main() {
    UserRepositoryCsvImpl data;
    CrudRepository<User, int>* repository;
    repository = new UserRepositoryCsvImpl;

    auto users = repository->getAll();
    for(auto& user: users) {
        std::cout << user << std::endl;
    }
}