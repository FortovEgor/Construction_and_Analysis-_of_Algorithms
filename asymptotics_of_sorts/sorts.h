/* 
Данный файл содержит реализации следующих 13 сортировок:
1) выбором
2) пузырьком
3) пузырьком с условием Айверсона 1g++ sorts.cpp -std=c++17 -O2
4) пузырьком с условием Айверсона 1+2
5) простыми вставками
6) бинарными вставками
7) подсчетом (устойчивая)
8) цифровой
9) слиянием
10) быстрой (первый опорный)
11) пирамидальной
12) Шелла (последовательность Циура)
13) Шелла (последовательность Шелла)
*/

uint64_t counter = 0;  // глобальный счетчик элементарных операций
/* ПРИМЕЧАНИЕ:
 кол-во элементарных операций инструкции = 
 = кол-во строчек ассемблерного кода этой инструкции
*/

// 1) Сортировка выбором
void selectionSort(std::vector<int>& vec, int size) {
    ++counter;  // инициализация счетчика i (регистр)
    counter += 3;  // условие 
    for (int i = 0; i < size - 1; ++i, counter += 4) {
        int min_index = i; 
        ++counter;
        
        // ищем минимум в правой, неотсортированной части массива
        counter += 3;  // инициализация счетчика j (регистр)
        for (int j = i + 1; j < size; ++j, counter += 2) {
            counter += 3;  // для сравнения
            if (vec[j] < vec[min_index]) {  // vec[j] - новый минимум
                min_index = j;
                ++counter;  // для обновления min_index
            }
        }
        counter += 1;  // для сравнения, операнды уже лежат в регистрах
        if (min_index != i) {  // элемент стоит не на своем месте
            std::swap(vec[i], vec[min_index]);
            counter += 4;
        }

    }
}

// 2) Сортировка пузырьком
void bubbleSort(std::vector<int>& vec, int size) {
    ++counter;  // i
    counter += 3;  // условие
    for (int i = 0; i < size - 1; ++i, counter += 4) {
        ++counter;  // j
        counter += 4;
        for (int j = 0; j < size - 1 - i; ++j, counter +=5) {
            counter += 3;
            if (vec[j + 1] < vec[j]) {  // неверный порядок элементов, меняем местами
                std::swap(vec[j], vec[j + 1]);
                counter += 4;
            }
        }
    }
}

// 3) Сортировка пузырьком с условием Айверсона 1
void bubbleSortWithIverson1(std::vector<int>& vec, int size) {
    int i = 0;
    bool t = true;  // если на предыдущей внутренней итерации не было заменов, сортировка окончена
    counter += 2;
    while (t) {
        t = false;
        counter += 2;
        counter += 4;
        for (int j = 0; j < size - i - 1; ++j, counter += 5) {
            counter += 3;
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                t = true;
                counter += 5;
            }
        }
        ++i;
        counter += 2;
    }
}

// 4) Сортировка пузырьком с условием Айверсона 1+2
void bubbleSortWithIverson1And2(std::vector<int>& vec, int size) {
    int i = 0;
    bool t = true;
    int bound = size - 1;  // изменяемое (в меньшую сторону) количество итераций для внутреннего цикла
    int temp;
    counter += 6;
    while (t) {
        t = false;
        temp = 0;
        counter += 4;
        for (int j = 0; j < bound; ++j, counter += 2) {
            counter += 3;
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                t = true;
                temp = j;
                counter += 6;
            }
        }
        bound = temp;
        ++i;
        counter += 3;
    }
}

// 5) Сортировка простыми вставками
void sortInsertion(std::vector<int>& vec, int size) {
    int key, j;
    counter += 4;
    for (int i = 1; i < size; ++i, counter += 2) {
        key = vec[i];
        j = i - 1;
        counter += 3;
        counter += 4;
        while (j >= 0 && vec[j] > key) {  // ищем место куда вставить элемент
            vec[j + 1] = vec[j];
            --j;
            counter += 5 + 3;
        }
        vec[j + 1] = key;
        counter += 3;
    }
}

// 6) Сортировка бинарными вставками
// бинарный поик для сортировки бинарными вставками
int binarySearch(const std::vector<int>& vec, int elem, int left_index, int right_index) {
    ++counter;
    if (left_index >= right_index) {
        ++counter;
        if (elem > vec[left_index]) {
            counter += 4;
            return left_index + 1;
        } else {
            counter += 4;
            return left_index;
        }
    }
        
    
    int mid = (left_index + right_index) / 2;
    counter += 4;
 
    ++counter;
    if (elem == vec[mid]) {
        counter += 3;
        return mid + 1;
    }
 
    counter += 2;
    if (elem > vec[mid]) {
        counter += 8;
        return binarySearch(vec, elem, mid + 1, right_index);
    } else {
        counter += 8;
        return binarySearch(vec, elem, left_index, mid - 1);
    }

}

// сама функция сортировки
void sortBinInsertion(std::vector<int>& vec, int size) {
    int j, k;
    counter += 4;
    for (int i = 1; i < size; ++i, counter += 2) {
        j = i - 1;
        counter += 2;
        k = binarySearch(vec, vec[i], 0, j);  // ищем подходящее место в массиве для вставки элемента
        counter += 8;
        for (int m = j; m >= k; --m, counter += 2) {
            std::swap(vec[m], vec[m+1]);
            counter += 4;
        }
    }
}

// 7) Сортировка подсчетом (устойчивая)
void stableCountingSort(std::vector<int>& vec, int size) {
    std::vector<int> b(size + 1, 0);  // массив для устойчивости сортировки
    counter += size + 2;
    int max_element = vec[0];
    ++counter;

    ++counter;
    for (int elem : vec) {
        ++counter;
        ++counter;
        if (elem > max_element) {
            max_element = elem;
            ++counter;
        }
    }

    counter += max_element + 2;
    std::vector<int> count(max_element+1, 0);  // ключевой массив стандартной сортировки подсчетом
    counter += 2;
    for (int i = 0; i < size; ++i, counter += 2) {
        ++count[vec[i]];
        counter += 3;
    }

    counter += 2;
    for (int i = 1; i <= max_element; ++i, counter += 2) {
        count[i] += count[i - 1];
        counter += 4;
    }
    counter += 3;
    for (int i = size - 1; i >= 0; --i, counter += 2) {
        b[--count[vec[i]]] = vec[i];
        counter += 5;
    }

    counter += 2;
    for (int i = 0; i < size; ++i, counter += 2) {
        vec[i] = b[i];
        counter += 2;
    }
}

// 8) Цифровая сортировка (по основанию 256)
// промежуточная функция
void count(std::vector<int>& vec, int exp) {
    int temp[vec.size()];
    int digits[256] = {0};
    int len = vec.size();
    counter += 260;

    counter += 2; 
    for (int i = 0; i < len; ++i, counter += 2) {
        ++digits[(vec[i] / exp) % 256];
        counter += 6;
    }

    counter += 3;
    for (int i = 1; i < 256; ++i, counter += 3) {
        digits[i] += digits[i - 1];
        counter += 4;
    }

    counter += 3;
    for (int i = len - 1; i >= 0; --i, counter += 2) {
        temp[digits[(vec[i] / exp) % 256] - 1] = vec[i];
        counter += 8;
        --digits[(vec[i] / exp) % 256];
        counter += 6;
    }

    counter += 2;
    for (int i = 0; i < len; ++i, counter += 2) {
        vec[i] = temp[i];
        counter += 2;
    }
}

// сама функция сортировки
void radixSort(std::vector<int>& vec, int size) {
    // находим максимум и берем от него логарифм по основанию 256
    int64_t max = *std::max_element(begin(vec), end(vec));
    counter += (size + 1) * 3 + 1;
    counter += 3;
    for (int64_t i = 1; max / i > 0; i *= 256, counter += 4) {
        counter += 3;
        count(vec, i);
    }
}

// 9) Сортировка слиянием
// промежуточная функция
void merge(std::vector<int>& vec, int left, int mid, int right) {
    std::vector<int> temp;
    counter += 2;
    temp.reserve(right - left);  // ДЛЯ УСКОРЕНИЯ
    counter += 2;
    int index = left, j = mid + 1;
    counter += 2;
    counter += 4;
    while (index <= mid && j <= right) {
        counter += 3;
        if (vec[index] <= vec[j]) {
            temp.push_back(vec[index]);
            ++index;
            counter += 4;
        }
        else {
            temp.push_back(vec[j]);
            ++j;
            counter += 4;
        }
        counter += 4;
    }

    ++counter;
    while (index <= mid) {
        temp.push_back(vec[index]);
        ++index;
        counter += 4;
        ++counter;
    }

    ++counter;
    while (j <= right) {
        temp.push_back(vec[j]);
        ++j;
        counter += 4;
        ++counter;
    }

    counter += 2;
    for (int i = left; i <= right; ++i, counter += 2) {
        vec[i] = temp[i - left];
        counter += 4;
    }

}

// сама функция сортировки
void mergeSortRecursive(std::vector<int>& vec, int left, int right) {
    ++counter;
    if (left < right) {
        int m = (left + right) / 2;
        counter += 3;
        counter += 4;
        mergeSortRecursive(vec, left, m);
        counter += 5;
        mergeSortRecursive(vec, m + 1, right);
        counter += 5;
        merge(vec, left, m, right);
    }
}

// шаблонная обертка
void mergeSort(std::vector<int>& vec, int size) {
    counter += 5;
    mergeSortRecursive(vec, 0, size - 1);
}

// 10) Быстроая сортировка (первый опорный)
// делим массив на два подмассива по опорному элементу
int partition(std::vector<int>& vec, int left, int right)
{
    int pivot = vec[left];  // пивот - первый опорный элемент
    int k = right;
    counter += 5;
    for (int i = right; i > left; i--, counter += 2) {
        counter += 3;
        if (vec[i] > pivot) {
            std::swap(vec[i], vec[k]);
            --k;
            counter += 5;
        }
    }
    std::swap(vec[left], vec[k]);
    counter += 4;
    counter += 2;
    return k;
}

// рекуривная реализация быстрой сортировки
void quickSortRecursive(std::vector<int>& vec, int left, int right) {
    ++counter;
    if (left < right) {
        counter += 5;
        int mid = partition(vec, left, right);  // пивот
 
        counter += 5;
        quickSortRecursive(vec, left, mid - 1);
        counter += 5;
        quickSortRecursive(vec, mid + 1, right);
    }
}

// сама шаблонная функция сортировки
void quickSort(std::vector<int>& vec, int size) {
    counter += 5;
    quickSortRecursive(vec, 0, size-1);
}

// 11) Пирамидальная сортировка
// промежуточная функция
void heapifyIterative(std::vector<int>& vec, int n, int i) {
    int maximum = i;
    int left, right;
    counter += 3;
    for (;;) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        counter += 6;
        counter += 1 + 3;
        if (left < n && vec[left] > vec[maximum]) {
            maximum = left;
            ++counter;
        }

        counter += 4;
        if (right < n && vec[right] > vec[maximum]) {
            maximum = right;
            ++counter;
        }

        ++counter;
        if (maximum == i) {
            break;
        } else {
            std::swap(vec[i], vec[maximum]);
            i = maximum;
            counter += 5;
        }
    }
}

// строим кучу размера n с макс. элементом с индексом i
void buildHeap(std::vector<int>& vec, int n) {
    counter += 2;
    for (int i = n / 2; i >= 0; --i, counter += 3) {
        counter += 4;
        heapifyIterative(vec, n, i);
    }
}

// сама сортировка
void heapSort(std::vector<int>& vec, int n) {
    counter += 3;
    buildHeap(vec, n);

    counter += 2;
    for (int i = n - 1; i >= 0; --i, counter += 2) {
        std::swap(vec[0], vec[i]);
        counter += 4;
        counter += 4;
        heapifyIterative(vec, i, 0);
    }
}

// 12) Сортировка Шелла (последовательность Циура)
void shellSortCiurSequence(std::vector<int>& vec, int size) {
    std::vector<int> gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    counter += 16;
    counter += 2;
    for (int index = 0; index < 8; ++index, counter += 2) {
        int d = gaps[index];
        counter += 3; 
        for (int i = d; i < size; ++i, counter += 2) {
            counter += 2;
            for (int j = i - d; j >= 0 && vec[j] > vec[j + d]; j -= d, counter += 6) {
                std::swap(vec[j], vec[j + d]);
                counter += 4;
            }
        }
    }
}

// 13) Сортировка Шелла (последовательность Шелла)
void shellSortShellSequence(std::vector<int>& vec, int size) {
    counter += 2;
    for (int d = size / 2; d > 0; d /= 2, counter += 2) {
        counter += 2;
        for (int i = d; i < size; ++i, counter += 2) {
            counter += 6;
            int temp = vec[i];
            int j;
            counter += 7;
            for (j = i; j >= d && vec[j - d] > temp; j -= d, counter += 6) {
                vec[j] = vec[j - d];
                counter += 4;
            }
            vec[j] = temp;
            ++counter;
        }
    }
}

void (*sorting_funcs[13])(std::vector<int>&, int) = 
    {selectionSort, bubbleSort, bubbleSortWithIverson1, bubbleSortWithIverson1And2, 
     sortInsertion, sortBinInsertion, stableCountingSort, radixSort, mergeSort,
     quickSort, heapSort, shellSortCiurSequence, shellSortShellSequence};

