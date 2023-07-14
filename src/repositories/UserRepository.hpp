#pragma once

#include "repositories/CrudRepository.hpp"
#include "model/User.hpp"

class UserRepository: public CrudRepository<User, uint32_t> {};