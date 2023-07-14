#pragma once

#include "UserRepository.hpp"

class UserRepositoryBinImpl final : public UserRepository {
public:
    uint32_t save(const User &item) override;
    std::optional<User> getById(uint32_t id) override;
    void update(uint32_t id, const User &item) override;
    void deleteById(uint32_t id) override;
    std::vector<User> getAll() override;
};