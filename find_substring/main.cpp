// ******************** КДЗ №2 ******************** //
// ****************** Фортов Егор ***************** //
// ******************** БПИ214 ******************** //
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "KMP_sophisticated_edges.hpp"
#include "KMP_standart_edges.hpp"
#include "native_algo.hpp"
#include "z_function.hpp"

#define SIZE_10K 10'000
#define SIZE_100K 100'000
#define REPEARED_ITERATIONS 9

void printVector(const std::vector<int>& vec) {
    for (int elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

uint64_t (*funcs[4]) (const std::string& p, const std::string& t) = {native_algo, KMP_standart, KMP_optimized, z_function};
std::string func_names[4] = {"Наивный_алгоритм", "КМП_стандарт", "КМП_утонченный", "Z_функция"};
std::string filenames[2] = {"table_1_new.csv", "table_2_new.csv"};

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<int> vec;

    int table_index = 0;
    std::ofstream file;
    file.open(filenames[table_index]);
    file << "Длина паттерна в символах;Тип шаблона;Наивный Алгоритм;КМП стандарт;КМП утонченный;Z-функция\n";

    srand(time(NULL));
// ************************* ЧАCТЬ 1 ************************* //
    // Текст для поиска шаблона:
// 1. Случайно сгенерированный текст в бинарном алфавите - 10'000 символов
// 2. Случайно сгенерированный текст в бинарном алфавите - 100'000 символов
// 3. Случайно сгенерированный текст в алфавите из 4 символов - 10'000 символов
// 4. Случайно сгенерированный текст в алфавите из 4 символов - 100'000 символов
    for (int text_var = 1; text_var <= 4; ++text_var) {
        std::cout << "TEXT_VARIANT: " << text_var << '\n';
        int current_size = (text_var == 1 || text_var == 3) ? SIZE_10K : SIZE_100K;
        int letters_count = (text_var == 1 || text_var == 2) ? 2 : 4;
        std::string s1(current_size, '1');
        for (char& el : s1) {
            el = static_cast<char>(rand() % letters_count + 48);
        }

        std::string substring;
        int index_of_substring;
        for (int num = 100; num <= 3'000; num += 100) {  // num - длина исходного шаблона
            index_of_substring = rand() % (current_size - num);
            substring = s1.substr(index_of_substring, num);

            switch (text_var) {
                case 1:
                file << num << ";" << "Случайно сгенерированный текст в бинарном алфавите - 10'000 символов;";
                break;
                case 2:
                file << num << ";" << "Случайно сгенерированный текст в бинарном алфавите - 100'000 символов;";
                break;
                case 3:
                file << num << ";" << "Случайно сгенерированный текст в алфавите из 4 символов - 10'000 символов;";
                break;
                case 4:
                file << num << ";" << "Случайно сгенерированный текст в алфавите из 4 символов - 100'000 символов;";
            }
            for (int method_index = 0; method_index < 4; ++method_index) {
                std::vector<uint64_t> operations_count(REPEARED_ITERATIONS);
                for (int i = 0; i < REPEARED_ITERATIONS; ++i) {
                    operations_count[i] = funcs[method_index](substring, s1);
                    funcs[method_index](substring, s1);
                }
                uint64_t sum = 0;
                for (int elem : operations_count) {
                    sum += elem;
                }
                uint64_t current_result = sum / 25;  // ОТВЕТ
                
                // log into .csv file
                file << current_result << ';';
            }
            file << '\n';
            std::cout << "num: " << num;
            std::cout << '\n';
        }
    }
    file.close();

/* ГРАФИКИ (4):
• Без символов подстановки, 10000 символов, бинарный алфавит
• Без символов подстановки, 10000 символов, 4-символьный алфавит 
• Без символов подстановки, 100000 символов, бинарный алфавит
• Без символов подстановки, 100000 символов, 4-символьный алфавит
*/


// ************************* ЧАCТЬ 2 ************************* //
    std::cout << "################## PART 2 ##################" << '\n';
    table_index = 1;
    file.open(filenames[table_index]);
    file << "Длина паттерна в символах;Тип шаблона;Наивный Алгоритм;КМП стандарт;КМП утонченный;Z-функция\n";
    // X - количество символов подстановки в шаблоне
    for (int X = 1; X <= 4; ++X) {
        for (int text_var = 1; text_var <= 4; ++text_var) {
            std::cout << "TEXT_VARIANT: " << text_var << " X: " << X << '\n';
            int current_size = (text_var == 1 || text_var == 3) ? SIZE_10K : SIZE_100K;
            int letters_count = (text_var == 1 || text_var == 2) ? 2 : 4;
            std::string s1(current_size, '1');
            for (char& el : s1) {
                el = static_cast<char>(rand() % letters_count + 48);
            }

            std::string substring;
            int index_of_substring;
            for (int num = 100; num <= 3'000; num += 100) {  // num - длина исходного шаблона
                index_of_substring = rand() % (current_size - num);
                substring = s1.substr(index_of_substring, num);
                std::vector<int> indexes_of_substitution;
                for (int jj = 1; jj <= X; ++jj) {
                    int random_pos = rand() % substring.size();
                    while (substring[random_pos] == '?') {
                        random_pos = rand() % substring.size();
                    }
                    substring[random_pos] = '?';
                    indexes_of_substitution.push_back(random_pos);
                }
                switch (text_var) {
                    case 1:
                    file << num << ";" << "Случайно сгенерированный текст в бинарном алфавите - 10'000 символов (" + std::to_string(X) + " символов подстановки);";
                    break;
                    case 2:
                    file << num << ";" << "Случайно сгенерированный текст в бинарном алфавите - 100'000 символов (" + std::to_string(X) + " символов подстановки);";
                    break;
                    case 3:
                    file << num << ";" << "Случайно сгенерированный текст в алфавите из 4 символов - 10'000 символов (" + std::to_string(X) + " символов подстановки);";
                    break;
                    case 4:
                    file << num << ";" << "Случайно сгенерированный текст в алфавите из 4 символов - 100'000 символов (" + std::to_string(X) + " символов подстановки);";
                }
                for (int method_index = 0; method_index < 4; ++method_index) {
                    std::vector<uint64_t> operations_count(REPEARED_ITERATIONS);
                    for (int i = 0; i < REPEARED_ITERATIONS; ++i) {
                        auto start_time = std::chrono::high_resolution_clock::now();
                        // в substring X символов подстановки ('?')
                        // в indexes_of_substring лежат их индексы
                        switch (X) {
                            case 1: 
                                if (num == 1 || num == 2) {  // бинарный алфавит
                                    for (int sub1 = 0; sub1 <= 1; ++sub1) {
                                        substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                        operations_count[i] += funcs[method_index](substring, s1);
                                    }
                                } else {  // num == 3 || num == 4
                                    for (int sub1 = 0; sub1 <= 3; ++sub1) {
                                        substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                        // vec = funcs[method_index](substring, s1);
                                        operations_count[i] += funcs[method_index](substring, s1);
                                    }
                                }
                                break;
                            case 2:
                                if (num == 1 || num == 2) {  // бинарный алфавит
                                    for (int sub1 = 0; sub1 <= 1; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 1; ++sub2) {
                                            substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                            substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                            operations_count[i] += funcs[method_index](substring, s1);
                                        }
                                    }
                                } else {  // num == 3 || num == 4
                                    for (int sub1 = 0; sub1 <= 3; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 3; ++sub2) {
                                            substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                            substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                            operations_count[i] += funcs[method_index](substring, s1);
                                        }
                                    }
                                }
                                break;
                            case 3:
                                if (num == 1 || num == 2) {  // бинарный алфавит
                                    for (int sub1 = 0; sub1 <= 1; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 1; ++sub2) {
                                            for (int sub3 = 0; sub3 <= 1; ++sub3) {
                                                substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                                substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                                substring[indexes_of_substitution[2]] = static_cast<char>(sub3 + 48);
                                                operations_count[i] += funcs[method_index](substring, s1);
                                            }
                                        }
                                    }
                                } else {  // num == 3 || num == 4
                                    for (int sub1 = 0; sub1 <= 3; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 3; ++sub2) {
                                            for (int sub3 = 0; sub3 <= 3; ++sub3) {
                                                substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                                substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                                substring[indexes_of_substitution[2]] = static_cast<char>(sub3 + 48);
                                                operations_count[i] += funcs[method_index](substring, s1);
                                            }
                                        }
                                    }
                                }
                                break;
                            default:  // case 4
                                if (num == 1 || num == 2) {  // бинарный алфавит
                                    for (int sub1 = 0; sub1 <= 1; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 1; ++sub2) {
                                            for (int sub3 = 0; sub3 <= 1; ++sub3) {
                                                for (int sub4 = 0; sub4 <= 1; ++sub4) {
                                                    substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                                    substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                                    substring[indexes_of_substitution[2]] = static_cast<char>(sub3 + 48);
                                                    substring[indexes_of_substitution[3]] = static_cast<char>(sub4 + 48);
                                                    operations_count[i] += funcs[method_index](substring, s1);
                                                }
                                            }
                                        }
                                    }
                                } else {  // num == 3 || num == 4
                                    for (int sub1 = 0; sub1 <= 3; ++sub1) {
                                        for (int sub2 = 0; sub2 <= 3; ++sub2) {
                                            for (int sub3 = 0; sub3 <= 3; ++sub3) {
                                                for (int sub4 = 0; sub4 <= 3; ++sub4) {
                                                    substring[indexes_of_substitution[0]] = static_cast<char>(sub1 + 48);
                                                    substring[indexes_of_substitution[1]] = static_cast<char>(sub2 + 48);
                                                    substring[indexes_of_substitution[2]] = static_cast<char>(sub3 + 48);
                                                    substring[indexes_of_substitution[3]] = static_cast<char>(sub4 + 48);
                                                    operations_count[i] += funcs[method_index](substring, s1);
                                                }
                                            }
                                        }
                                    }
                                }
                        }

                    }
                    uint64_t sum = 0;
                    for (int elem : operations_count) {
                        sum += elem;
                    }
                    uint64_t current_result = sum / 25;  // ОТВЕТ
                    
                    // log into .csv file
                    file << current_result << ';';
            }
            file << '\n';
            std::cout << "num: " << num;
            std::cout << '\n';
        }
        }
    }
    file.close();
/* ГРАФИКИ (16):
• С X символов подстановки, 10000 символов, бинарный алфавит (X = 1, 2, 3, 4)
• С X символов подстановки, 10000 символов, 4-символьный алфавит (X = 1, 2, 3, 4)
• С X символов подстановки, 100000 символов, бинарный алфавит (X = 1, 2, 3, 4)
• С X символов подстановки, 100000 символов, 4-символьный алфавит (X = 1, 2, 3, 4)
*/
    return 0;
}