//
// Created by bogdan on 11.07.2023.
//
#pragma once

#include <vector>
#include <optional>

template <typename T, typename K>
class CrudRepository {
public:
    virtual ~CrudRepository() = default;
    virtual K save(const T& item) = 0;
    virtual std::optional<T> getById(K id) = 0;
    virtual void update(K id, const T& item) = 0;
    virtual void deleteById(K id) = 0;
    virtual std::vector<T> getAll() = 0;
};
