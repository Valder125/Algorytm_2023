#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <set>


using namespace std;
const int firstSize = 100;//розмір першого масиву
long FirstArr[firstSize];//оголошення першого масиву
int choice;//змінна для вибору операції
int min_value=0, max_value=0;//мінімальне та максимальне значення випадкових чисел для елементів масиву
int secondSize = 0;//знаходження кількості елементів в другому масиві
long* SecondArr = new long[secondSize];//оголошення другого масиву
//заповнення масиву
void fillMass() {
    do {
        std::cout << "Введіть спершу мінімальне а потім максимальне значення випадкових чисел для масиву\n";
        srand(static_cast<unsigned>(time(0)));//генератор випадкових чисел
        std::set<int> uniqueNumbers;//налаштування унікальних чисел
        std::cin >> min_value>> max_value;//ввід мінімалььного і максимального значення випадкових чисел
        if (min_value >= max_value) {
            std::cout << "Помилка!!! Мінімальне число діапазону більше за максимальне\n";
        }
        else if (((max_value - min_value))+1 < firstSize) {
            std::cout << "Помилка!!! Кількість чисел в діапазоні менше за розмір масиву\n";
        }
        else {
            uniqueNumbers.clear();//очищення минулих випадкових чисел для коректної роботи програми
            //процес заповнення масиву випадковими числами
            for (int i = 0; i < firstSize; i++) {
                int randomNumber;
                do {
                    randomNumber = std::rand() % (max_value - min_value+1)+min_value;
                } while (uniqueNumbers.count(randomNumber) > 0);
                FirstArr[i] = randomNumber;
                uniqueNumbers.insert(randomNumber);
            }
        }
    } while (min_value>=max_value or ((max_value-min_value))+1<firstSize);
    std::cout<< "Масив успішно заповнено"<<endl;
}

//показ першого масиву
void showMass() {
    int sum=0;
    //цикл для перевірки можливості операції
    for (int i = 0; i < firstSize; i++) {    
        sum += std::abs(FirstArr[i]);
    }
    if (sum == 0) {
        std::cout << "Помилка!!! Масив незаповнеий\n";
    }
    else {
        //вивід масиву
        for (int i = 0; i < firstSize; i++) {
            std::cout<< (FirstArr[i]) << " ";
        }
        std::cout << "\nМасив успішно виведено" << endl;
    }   
}
//виконання першого завдання
void firstQuest() {
    int sum = 0;
    //цикл для перевірки можливості операції
    for (int i = 0; i < firstSize; i++) {
        sum += std::abs(FirstArr[i]);
    }
    if (sum == 0) {
        std::cout << "Помилка!!! Масив незаповнеий\n";
    }
    else {
        //оголошення змінних для найбільшого та найменшого числа в масиві
        int  max_number = FirstArr[0];
        int min_number = FirstArr[0];
        std::cout << "\nДругий масив" << endl;
        int j, k = 1;//змінні для операцій з числами в проміжку між максимальним і мінімальним значеннями масиву відповідно
        //знаходження мінімального і максимального елементів масиву
        for (j = 1; j < firstSize; j++) {
            if (FirstArr[j] > max_number) {
                max_number = FirstArr[j];
            }
            else if (FirstArr[k] < min_number) {
                min_number = FirstArr[k];
            }
            k++;
        }
        for (int i = 0; i < firstSize; i++) {
            if (max_number == FirstArr[i]) {
                j = i;
            }
            if (min_number == FirstArr[i]) {
                k = i;
            }
        }
        if (std::abs(j - k) == 1) {
            std::cout << "Не існує чисел між мінімальним та максимальним елементами масиву" << endl;

        }
        else {
            secondSize = std::abs(j - k) - 1;//знаходження кількості елементів в другому масиві
            //заповнення другого масиву
            if (k > j) {
                j++;
                for (int i = 0; i < secondSize; i++) {
                    if (j < k) {
                        SecondArr[i] = FirstArr[j];
                        std::cout << SecondArr[i] << " ";
                        j++;
                    }
                }
            }
            else if (j > k) {
                j--;
                for (int i = 0; i < secondSize; i++) {
                    if (k < j) {
                        SecondArr[i] = FirstArr[j];
                        std::cout << SecondArr[i] << " ";
                        j--;
                    }
                }
            }
            std::cout << endl;
        }
    }  
}
//виконання другого завдання
void secondQuest() {
    int n = 0;
    //перевірка можливості виконання другого завдання
    if (secondSize <= 1) {
        std::cout << "Зміна другого масиву неможлива, бо він складається лише з одного числа або не існує" << endl;
    }
    else {
        std::cout << "Другий масив після перетворення" << endl;
        //заповнення другого масиву після перетворення 
        for (int i = 0; i < secondSize; i++) {
            if (i != 0) {
                n = i - 1;
                if (SecondArr[n] % 2 == 0) {
                    if (SecondArr[i] % 2 == 1 || SecondArr[i] % 2 == -1) {
                        SecondArr[i] = SecondArr[i] * SecondArr[i];
                    }
                }
            }
            std::cout << SecondArr[i] << " ";
            
        }
        std::cout << endl;
    }
    std::cout << endl; 
}
int main()
{
    //Додавання української мови. При використанні в онлайн-компіляторі слід закоментувати як і бібліотеку Windows.h
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    do {
        cout << "1. Заповнити масив\n";
        cout << "2. Вивести масив на екран\n";
        cout << "3. Завдання 1\n";
        cout << "4. Завдання 2\n";
        cout << "5. Вихід\n";
        cin >> choice;
        switch (choice) {
        case 1: fillMass();
            break;
        case 2: showMass();
            break;
        case 3:firstQuest();
            break;
        case 4:secondQuest();
            break;
        }
    } while (choice != 5);
    return 0;
}