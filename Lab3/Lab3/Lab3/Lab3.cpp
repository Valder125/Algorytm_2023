#include <iostream>
#include <stack>
#include <Windows.h>
#include <ctime>
#include <future>


using namespace std;

void firstQuest() {
    // Створюємо стек для зберігання цілих чисел
    std::stack<int> myStack;
    // Заповнюємо стек числами, введеними з клавіатури
    int n;
    std::cout << "Введіть кількість елементів у стеку: ";
    std::cin >> n;

    std::cout << "Введіть цілі числа для стеку:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        myStack.push(value);
    }

    // Виводимо стек на екран у зворотньому порядку
    std::cout << "Елементи стеку у зворотньому порядку:\n";
    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
    std::cout << "\n";
}
void secondQuest() {
    // Створюємо стеки для парних і непарних чисел
    std::stack<int> evenStack;
    std::stack<int> oddStack;

    // Заповнюємо стеки числами, введеними з клавіатури
    int n1;
    std::cout << "Введіть кількість елементів: ";
    std::cin >> n1;

    std::cout << "Введіть цілі числа:\n";
    for (int i = 0; i < n1; ++i) {
        int value;
        std::cin >> value;

        // Визначаємо, чи є число парним чи непарним
        if (value % 2 == 0) {
            evenStack.push(value);  // Додаємо парне число до стеку для парних чисел
        }
        else {
            oddStack.push(value);   // Додаємо непарне число до стеку для непарних чисел
        }
    }

    // Виводимо стек парних чисел
    std::cout << "Елементи стеку парних чисел:\n";
    while (!evenStack.empty()) {
        std::cout << evenStack.top() << " ";
        evenStack.pop();
    }

    std::cout << "\n";

    // Виводимо стек непарних чисел
    std::cout << "Елементи стеку непарних чисел:\n";
    while (!oddStack.empty()) {
        std::cout << oddStack.top() << " ";
        oddStack.pop();
    }
    std::cout << "\n";
}
bool isBalanced(const std::string& sequence) {
    std::stack<char> brackets;

    for (char bracket : sequence) {
        if (bracket == '(' || bracket == '[') {
            brackets.push(bracket);  // Додаємо відкриту дужку до стеку
        }
        else if (bracket == ')' || bracket == ']') {
            // Перевіряємо відповідність закритої дужки відкритій
            if (brackets.empty() ||
                (bracket == ')' && brackets.top() != '(') ||
                (bracket == ']' && brackets.top() != '[')) {
                return false;
            }
            brackets.pop();  // Видаляємо відповідну відкриту дужку зі стеку
        }
    }

    return brackets.empty();
}
int main() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int choice = 0;
    do {
        cout << "1. Вивід стеку з цілими числами на екран в зворотньому порядку\n";
        cout << "2. Вивід двох стеків з парними та непарними числами серед введених з клавіатури\n";
        cout << "3. Перевірка правильності введення дужок за 10 секунд часу\n";
        cout << "4. Вихід\n";
        cout << "\nВиберіть дію: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            firstQuest();
            break;
        case 2:
            secondQuest();
            break;
        case 3: {
            std::string sequence;
            std::cout << "Введіть послідовність дужок: ";

            // Використовуємо std::async для асинхронного вводу
            auto inputFuture = std::async(std::launch::async, [&]() {
                std::cin >> sequence;
                }
            );
            const double maxExecutionTime = 10.0;


            // Очікуємо завершення вводу протягом вказаного максимального часу
            auto status = inputFuture.wait_for(std::chrono::seconds(static_cast<int>(maxExecutionTime)));
            if (status == std::future_status::timeout) {
                std::cout << "\nВвід занадто довгий. Програма завершується. Введіть будь-який символ і натисніть ENTER для продовження\n";
                break;
            }
            else {
                // Перевіряємо баланс дужок
                if (isBalanced(sequence)) {
                    std::cout << "Послідовність правильна.\n";
                }
                else {
                    std::cout << "Послідовність НЕправильна.\n";
                }
            }  
            break;
        }         
        default:
            break;
        }
    } while (choice!=4);
    return 0;
}
