#pragma once

#include <fstream>

#include "UserRepository.hpp"

class UserRepositoryBinImpl final : public UserRepository {
public:
    UserRepositoryBinImpl();
    ~UserRepositoryBinImpl() override;
    uint32_t save(const User &item) override;
    std::optional<User> getById(uint32_t id) override;
    void update(uint32_t id, const User &item) override;
    void deleteById(uint32_t id) override;
    std::vector<User> getAll() override;
    void deleteAll() override;
private:
    std::vector<User> data;
    std::ifstream dataInput;
    std::ofstream dataOutput;
    uint32_t lastId;

    void openIn();
    void openOut();
    void read();
    void saveAll();
};