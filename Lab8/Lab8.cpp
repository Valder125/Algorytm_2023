#include <iostream>
#include <vector>
#include <regex>

// Оголошення функції Numbers, яку ми визначимо пізніше
std::vector<int> Numbers(const std::string& input);

namespace Lab8 {
    class Input {
    public:
        // Метод для отримання послідовності цілих чисел введеної користувачем
        static std::vector<int> Sequence() {
            std::cout << "Введіть послідовність цілих чисел: ";
            std::string input;
            std::getline(std::cin, input);

            // Викликаємо Numbers для отримання масиву цілих чисел
            return Numbers(input);
        }
    };

    // Оголошення функції Print, яку ми визначимо пізніше
    template <typename T>
    void Print(const T& array);
}

// Визначення функції Numbers
std::vector<int> Numbers(const std::string& input) {
    std::regex regex("-?\\d+");
    std::smatch match;
    std::vector<int> result;

    // Знаходимо всі цілі числа в рядку за допомогою регулярного виразу
    auto it = input.cbegin();
    while (std::regex_search(it, input.cend(), match, regex)) {
        result.push_back(std::stoi(match[0]));
        it = match.suffix().first;
    }

    return result;
}

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

class BinarySearcher {
private:
    const std::vector<int> _source;
    const std::vector<int> _sorted;
    std::vector<int> _result;

    // Метод для виконання бінарного пошуку для конкретного вхідного елемента
    void Find(int source, int first, int last) {
        if (first >= last) {
            // Умова виходу з рекурсії: діапазон не має елементів
            _result[source] = -1;
            return;
        }

        int middle = first + (last - first) / 2; // Знаходження середнього елемента діапазону

        if (_source[source] == _sorted[middle]) {
            // Елемент знайдено
            _result[source] = middle;
        }
        else if (_source[source] > _sorted[middle]) {
            // Рекурсивний виклик для правої половини
            Find(source, middle + 1, last);
        }
        else {
            // Рекурсивний виклик для лівої половини
            Find(source, first, middle);
        }
    }

public:
    // Конструктор класу
    BinarySearcher(const std::vector<int>& source, const std::vector<int>& sorted)
        : _source(source), _sorted(sorted), _result(source.size(), -1) {}

    // Метод для здійснення бінарного пошуку для всіх елементів вхідного масиву
    std::vector<int> Find() {
        for (int i = 0; i < _source.size(); i++) {
            Find(i, 0, _sorted.size());
        }
        return _result; // Повертаємо вектор результатів
    }
};

namespace Lab8 {
    // Визначення функції Print
    template <typename T>
    void Print(const T& array) {
        for (const auto& element : array) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Ввід послідовностей
    auto first = Lab8::Input::Sequence();
    auto second = Lab8::Input::Sequence();

    // Сортування першої послідовності та вивід відсортованої послідовності
    Sorter sorter;
    auto sortedFirst = sorter.QuickSort(first);
    Lab8::Print(sortedFirst);

    // Пошук елементів з другої послідовності в першій
    BinarySearcher searcher(second, sortedFirst);
    Lab8::Print(searcher.Find());

    return 0;
}