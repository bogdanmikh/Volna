#include "repositories/CrudRepository.hpp"
#include "repositories/UserRepositoryBinImpl.hpp"

#include <cstdlib>
#include <ctime>
#include <sstream>


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
    UserRepository* repository;
    repository = new UserRepositoryBinImpl;
    repository->save({"Bogdan", "Huligan123"});
    repository->save({"Artur", "Alee123"});
    repository->save({"Artuino", "Artuin0"});
    repository->save({"Misha", "IOS12"});
    for (User data: repository->getAll()) {
        std::cout << data << std::endl;
    }
    repository->deleteAll();
    delete repository;
}

