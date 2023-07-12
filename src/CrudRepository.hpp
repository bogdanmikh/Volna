//
// Created by bogdan on 11.07.2023.
//

template <typename T, typename K>
class CrudRepository {
public:
    K save(const T& item);
    T getById(K id);
    void update(K id, const T& item);
    void deleteById(K id);
};
