#include "repositories/CrudRepository.hpp"
#include "repositories/UserRepositoryCsvImpl.hpp"

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
    repository = new UserRepositoryCsvImpl;

    uint32_t id = repository->save({"Arduino", "JavaIsMyLove;)"});
    assert(repository->getById(id)->name == "Arduino");
    assert(repository->getById(id)->password == "JavaIsMyLove;)");
    repository->update(id, {"Arduino", "JavaIsMyLove:("});
    assert(repository->getById(id)->name == "Arduino");
    assert(repository->getById(id)->password == "JavaIsMyLove:(");
    //std::optional<User> user = repository->getById(1);
//    if (user) {
//        std::cout << user->id << ' ' << user->name << ' ' << user->password;
//    }
    repository->deleteById(1);
    assert(!repository->getById(1).has_value());
    delete repository;
}