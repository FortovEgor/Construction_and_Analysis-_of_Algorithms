// 1) АиСД-2, 2023, задание 5
// 2) Фортов Егор, БПИ214
// 3) VS Code
// 4) По максимуму
// 5) -

// компиляция: g++ main.cpp -std=c++17 -O2

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>
#include "sorts.h"
#include "extra.h"

int main(void) {
    std::vector<int> vect{5, 4, 3, 2, 1};
    shellSortCiurSequence(vect, vect.size());

    srand(time(nullptr));
    // Создаем и заполняем 1-ую таблицу: для диапазона размерностей [50, 300], шаг 50

    // Поля таблицы: Размер массива | Тип массива | Выбор | Пузырёк | Пузырек Айв1 |
    // Пузырек Айв1+2 | Вставки | Бин. вставки | Подсчет | Цифровая | Слияние |
    // Быстрая | Пирамидальная | Шелла-Циура | Шелла-Шелла

    std::string filenames[2] = {"table_1_new.csv", "table_2_new.csv"};
    int step[2] = {50, 100};
    int begin_size[2] = {50, 100};
    int end_size[2] = {300, 4100};

    for (int table_index = 0; table_index < 2; ++table_index) {
        std::cout << "///////////////////////// Таблица №" << table_index + 1 << " /////////////////////////\n";
        std::ofstream file;
        file.open(filenames[table_index]);
        file << "Размер массива;Тип массива;Выбор (time);Выбор (operations);Пузырёк (time);Пузырёк (operations);Пузырек Айв1 (time);"
             << "Пузырек Айв1 (operations);Пузырёк Айв1+2 (time);Пузырёк Айв1+2 (operations);"
             << "Вставки (time);Вставки (operations);Бин. вставки (time);Бин. вставки (operations);Подсчет (time);Подсчет (operations);"
             << "Цифровая (time);Цифровая (operations);Слияние (time);Слияние (operations);Быстрая (time);Быстрая (operations);"
             << "Пирамидальная (time);Пирамидальная (operations);"
             << "Шелла-Циура (time);Шелла-Циура (operations);Шелла-Шелла (time);Шелла-Шелла (operations)\n";  // записали названия колонок для таблицы №1
        // 1-ая таблица должна содержать 15 колонок и 6 * 4 строчек (6 размеров массивов, 4 типа массива на каждый размер)
        for (int size = begin_size[table_index]; size <= end_size[table_index]; size += step[table_index]) {
            std::cout << "Количество элементов в массиве: " << size << '\n';
            std::vector<int> vec(size), vec_copy;

            for (int option = 1; option <= 4; ++option) {
                switch (option) {
                    case 1:  // Случай №1: массив заполнен числами в диапазоне [0, 5]
                        for (int& elem : vec) {
                            elem = rand() % 6;
                        }
                        vec_copy = vec;  // сортировать будем копию массива
                        std::cout << size << ";случайные числа 0-5;";
                        file << size << ";случайные числа 0-5;";
                        break;
                    case 2:  // Случай №2: массив заполнен числами в диапазоне [0, 4000]
                        for (int& elem : vec) {
                            elem = rand() % 4001;
                        }
                        vec_copy = vec;  // сортировать будем копию массива
                        std::cout << size << ";случайные числа 0-4000;";
                        file << size << ";случайные числа 0-4000;";
                        break;
                    case 3:  // Случай №3: массив "почти" отсортирован
                        for (int& elem : vec) {
                            elem = rand() % 4001;
                        }
                        sort(vec.begin(), vec.end());
                        std::swap(vec[7], vec[size - 43]);  // для "почти" отсортированности (1)
                        std::swap(vec[55], vec[size - 99]);  // для "почти" отсортированности (2)
                        vec_copy = vec;  // сортировать будем копию массива
                        std::cout << size << ";почти отсортированный массив;";
                        file << size << ";почти отсортированный массив;";
                        break;
                    case 4:  // Случай №4: массив отсортирован в обратном порядке (по убыванию)
                        for (int& elem : vec) {
                            elem = rand() % 4100 + 1;
                        }
                        // сортировка в обратном порядке
                        sort(vec.begin(), vec.end(), [](const int lhs, const int rhs){ return lhs > rhs; });
                        vec_copy = vec;  // сортировать будем копию массива
                        std::cout << size << ";обратно отсортированный массив;";
                        file << size << ";обратно отсортированный массив;";
                        break;
                }

                for (int i = 0; i < 13; ++i) {  // запускаем все 13 сортировок
                    std::vector<uint64_t> nanoseconds(25);
                    for (int j = 0; j < 25; ++j) {
                        counter = 0;
                        auto start_time = std::chrono::high_resolution_clock::now();
                        sorting_funcs[i](vec_copy, size);
                        auto stop_time = std::chrono::high_resolution_clock::now();
                        // auto duration_time_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
                        auto duration_time_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time - start_time);
                        if (!isSorted(vec_copy)) {
                            std::cerr << "ERROR: Функция не отсортировала массив!\n";
                            exit(1);
                        }
                        vec_copy = vec;
                        nanoseconds[j] = duration_time_nanoseconds.count();
                    }
                    uint64_t sum = 0;
                    for (int elem : nanoseconds) {
                        sum += elem;
                    }
                    int current_result = static_cast<int>(sum / 25);
                    std::cout << current_result << ' ';
                    file << current_result << ';' << counter << ';';  // запись результата в файл .csv
                }
                std::cout << '\n';
                file << '\n';
            }
            std::cout << '\n';
        }
        file.close();
    }

    return 0;
}
