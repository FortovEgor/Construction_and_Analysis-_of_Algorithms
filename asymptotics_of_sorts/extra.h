void printVector(const std::vector<int>& vec) {
    std::cout << '\n';
    for (int elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

bool isSorted(const std::vector<int>& vec) {
    for (int i = 0; i < vec.size() - 1; ++i) {
        if (vec[i+1] < vec[i]) {
            return 0;
        }
    }
    return 1;
}