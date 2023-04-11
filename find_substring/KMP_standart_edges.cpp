// КМП со стандартными гранями
#include <iostream>
#include <vector>

std::vector<int> result_KMP_standart;

// P - подстрока; T - строка
uint64_t KMP_standart(const std::string& p, const std::string& t) {
    uint64_t OPERATIONS= 0;
    OPERATIONS += 3;
    if (p.size() > t.size()) {
        return OPERATIONS;
    }

    // найдем массив граней для подстроки P
    std::vector<int> br(p.size(), 0);
    OPERATIONS += p.size() + 3;
    for (int i = 0; i < static_cast<int>(p.size()) - 1; ++i) {
        int br_curr = br[i];
        OPERATIONS += 6;
        while (br_curr > 0 && p[i + 1] != p[br_curr]) {
            br_curr = br[br_curr - 1];
            OPERATIONS += 3;
            OPERATIONS += 5;
        }
        OPERATIONS += 5;
        if (p[i + 1] == p[br_curr]) {
            ++br_curr;
            ++OPERATIONS;
        }
        OPERATIONS += 3;
        br[i + 1] = br_curr;
    }

    // КМП
    int k = 0;
    int m = p.size(), n = t.size();
    OPERATIONS += 4;
    OPERATIONS += 3;
    for (int i = 0; i < n; ++i) {
        OPERATIONS += 5;
        while (k > 0 && p[k] != t[i]) {
            k = br[k - 1];
            OPERATIONS += 4;
        }
        OPERATIONS += 3;
        if (p[k] == t[i]) {
            ++k;
            ++OPERATIONS;
        }
        ++OPERATIONS;
        if (k == m) {
            result_KMP_standart.push_back(i - m + 1);
            k = br[m - 1];
            OPERATIONS += 7;
        }
    }

    return OPERATIONS;
}