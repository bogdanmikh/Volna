#include "UserRepository.hpp"

int main() {
    UserRepository data;
    data.addUser({"Misha", "Bombil"});
    std::cout << data.getUser(1) << std::endl;
    data.update({"Lapyh", "Alo123"}, 1);
  //  data.deleteUser(1);
}