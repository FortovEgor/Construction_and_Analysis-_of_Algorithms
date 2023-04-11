// нативный алгоритм поиска подстроки в строке
#include <iostream>
#include <vector>

std::vector<int> result_native_algo;

// P - подстрока; T - строка
uint64_t native_algo(const std::string& p, const std::string& t) {
    uint64_t OPERATIONS = 0;
    OPERATIONS += 3;
    if (p.size() > t.size()) {
        return OPERATIONS;
    }
    
    OPERATIONS += 5;
    for (int i = 0; i + p.size() <= t.size(); ++i) {
        OPERATIONS += 3;
        size_t equal_chars = 0;
        for (int j = 0; j < p.size(); ++j) {
            OPERATIONS += 5;
            if (p[j] == t[i+j]) {
                ++equal_chars;
                ++OPERATIONS;
            } else {
                break;
            }
            OPERATIONS += 4;
        }
        OPERATIONS += 3;
        if (equal_chars == p.size()) {
            result_native_algo.push_back(i);
            ++OPERATIONS;
        }
    }

    return OPERATIONS;
}