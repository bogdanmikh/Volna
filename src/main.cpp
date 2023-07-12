#include "UserRepository.hpp"

int main() {
    UserRepository data;
    data.addUser("Borya", "qwerty123");
    data.addUser("Misha", "Foo101020");
    data.addUser("Bogdan", "1q2w3e");
    data.addUser("Timur", "Kolya101");
    data.updateName(1, "Loh");
    data.updateName(2, "Developer for IOS");
    data.updatePassword(1, "Loshara123");
    data.updatePassword(2, "Output is one");
    data.deleteUser(1);
    data.getInfoUser(1);
    data.getInfoUser(2);
    data.getInfoUser(3);
    data.getInfoUser(4);
}