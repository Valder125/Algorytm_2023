// sorter.h
#pragma once

#include <vector>

class Sorter {
public:
    // ����������� �����
    Sorter() {}

    // ����� ��� ���������� ������� ������� �������
    std::vector<int> QuickSort(const std::vector<int>& input);

private:
    // ����� ��� ������������ ���������� ������� �������
    void QuickSortRecursive(std::vector<int>& array, int left, int right);
};

std::vector<int> Sorter::QuickSort(const std::vector<int>& input) {
    // ������� ������� ������, ��� �� �������� ����
    std::vector<int> sortedArray = input;

    // ��������� ���������� ������� ��� ����������
    QuickSortRecursive(sortedArray, 0, sortedArray.size() - 1);

    return sortedArray;
}

void Sorter::QuickSortRecursive(std::vector<int>& array, int left, int right) {
    // ����������� ����� � �������, ���� ������� ������ �� ����� ���� ��������
    if (left >= right) {
        return;
    }

    // �������� ������� �������
    int pivotIndex = (left + right) / 2;
    int pivotValue = array[pivotIndex];

    // ��������� ����� �� �� �������
    int i = left, j = right;
    while (i <= j) {
        while (array[i] < pivotValue) {
            i++;
        }
        while (array[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            // ���� �������
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    // ���������� ������� ����� �������
    QuickSortRecursive(array, left, j);
    QuickSortRecursive(array, i, right);
}
