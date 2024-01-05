#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

int main() {
    SetConsoleOutputCP(1251);

    // Крок 1: Користувач вводить число
    int userNumber;
    std::cout << "Введіть число: ";
    std::cin >> userNumber;

    // Крок 2: Генерація матриці випадкових чисел
    const int matrixSize = userNumber;
    std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));

    std::srand(std::time(0));

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            matrix[i][j] = std::rand() % 201 - 100;
        }
    }

    // Крок 3: Вивід матриці
    std::cout << "Матриця:" << std::endl;
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << std::setw(5) << matrix[i][j];
        }
        std::cout << std::endl;
    }

    // Крок 4: Пошук останнього від'ємного елемента та вивід його значення та координат
    int lastNegativeElement = matrix[0][0];
    int row = 0;
    int col = 0;

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            if (matrix[i][j] < 0) {
                lastNegativeElement = matrix[i][j];
                row = i;
                col = j;
            }
        }
    }

    std::cout << "Останній від'ємний елемент: " << lastNegativeElement << std::endl;
    std::cout << "Координати: рядок " << row << ", колонка " << col << std::endl;

    return 0;
}