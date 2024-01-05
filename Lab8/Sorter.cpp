// sorter.h
#pragma once

#include <vector>

class Sorter {
public:
    // Конструктор класу
    Sorter() {}

    // Метод для сортування вектора швидким методом
    std::vector<int> QuickSort(const std::vector<int>& input);

private:
    // Метод для рекурсивного сортування частини вектора
    void QuickSortRecursive(std::vector<int>& array, int left, int right);
};

std::vector<int> Sorter::QuickSort(const std::vector<int>& input) {
    // Копіюємо вхідний вектор, щоб не змінювати його
    std::vector<int> sortedArray = input;

    // Викликаємо рекурсивну функцію для сортування
    QuickSortRecursive(sortedArray, 0, sortedArray.size() - 1);

    return sortedArray;
}

void Sorter::QuickSortRecursive(std::vector<int>& array, int left, int right) {
    // Рекурсивний вихід з функції, якщо частина масиву має менше двох елементів
    if (left >= right) {
        return;
    }

    // Вибираємо опорний елемент
    int pivotIndex = (left + right) / 2;
    int pivotValue = array[pivotIndex];

    // Розбиваємо масив на дві частини
    int i = left, j = right;
    while (i <= j) {
        while (array[i] < pivotValue) {
            i++;
        }
        while (array[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            // Обмін значень
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    // Рекурсивно сортуємо обидві частини
    QuickSortRecursive(array, left, j);
    QuickSortRecursive(array, i, right);
}
