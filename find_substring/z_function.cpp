// Z-функция: поиск подстроки в строке
// Сложность: O(|s1| + |s2|), 
// где s1 - 1-ая строка, s2 - 2-ая строка

#include <iostream>
#include <vector>

std::vector<int> z;
std::vector<int> result_z_function;

uint64_t z_function (const std::string& p, const std::string& t) {
    uint64_t OPERATIONS = 0;
    std::string s = p + "#" + t;
	int n = (int) s.length();
    z.reserve(n);
    OPERATIONS += p.size() + 2 + t.size() + n;
    OPERATIONS += 5;
    for (int i = 0; i < n; ++i) {
        z.push_back(0);
        OPERATIONS += 4;
    }

    OPERATIONS += 2;
    int L = 0, R = 0;
    OPERATIONS += 5;
	for (int i = 1; i < n; ++i) {
        OPERATIONS += 5;
        z[i] = std::max(0, std::min(R - i + 1, z[i - L]));
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
            OPERATIONS += 7;
        }
        OPERATIONS += 3;
        if (i + z[i] > R) {
            L = i;
            R = i + z[i] + 1;
            OPERATIONS += 3;
        }
        OPERATIONS += 2;
        if (z[i] == p.size()) {
            ++OPERATIONS;
            result_z_function.push_back(i - p.size() - 1);
        }
	}
	return OPERATIONS;
}
