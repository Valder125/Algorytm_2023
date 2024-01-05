#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <Windows.h>
using namespace std;
    
    // Структура для дати народження
    struct Date {
        int day;
        int month;
        int year;


        // Конструктор за замовчуванням
        Date() : day(1), month(1), year(1900) {}
    };

    // Структура для роботи
    struct Job {
        bool employed=true;
        std::string profession;
        int experience=0;
    };

    // Структура для члена родини
    struct Person {
        std::string firstName;
        std::string lastName;
        Date birthDate;
        Job jobInfo;
    };

    // Структура для родини
    struct Family {
        Person husband;
        Person wife;
        std::list<Person> children;
    };

    std::list<Family> families;

    //Перше завдання
    void first() {
        std::list<int> numbers;
        int num = 0;

        std::cout << "Введіть цілі числа (для завершення введення введіть 0):\n";

        while (true) {
            std::cin >> num;

            if (num == 0) {
                break;
            }

        numbers.push_back(num);
    }

    std::cout << "Ваш список чисел:\n";
        for (const int& number : numbers) {
            std::cout << number << " ";
        }

        std::cout << "\n"; 
    }

    //Друге завдання
    void second() {
        std::string inputString;
        std::list<char> charList;

        std::cout << "Введіть рядок: ";
        std::cin.ignore(); 
        std::getline(std::cin, inputString);

        for (char c : inputString) {
            charList.push_back(c);
        }

        std::cout << "Результат - список символів: ";
        for (char c : charList) {
            std::cout << c << " ";
        }

        std::cout << "\n";
    }

    //Третє завдання
    void third() {
        std::string inputString;
        std::list<std::string> atoms;

        std::cout << "Введіть рядок: ";
        std::cin.ignore(); 
        std::getline(std::cin, inputString);
        inputString += " ";
        bool space = false;

        for (int i = 0; i < inputString.length(); i++) {
            if (inputString[i] == ' ' && space)
            {
                inputString = inputString.substr(0, i-1) + inputString.substr(i);
                i--;
            }

            space = inputString[i] == ' ';
        }


        for (int last = 0, first = 0; last < inputString.length(); last++) {
            if (inputString[last] == ' ') {
                atoms.push_back(inputString.substr(first, last - first));
                first = last + 1;
            }
        }
            
        std::cout << "Результат - список атомів: ";
        for (const std::string& atom : atoms)
            std::cout << atom << " | ";
        
        std::cout << endl;
        
    }       

    void getFamilyWithTwoChildren() {
        // Знаходимо та виводимо на екран родини з двома дітьми
        std::cout << "Родини з двома дітьми:\n";
        for (const Family& family : families) {
            if (family.children.size() == 2) {
                std::cout << "Чоловік: " << family.husband.firstName << " " << family.husband.lastName << std::endl;
                std::cout << "Дружина: " << family.wife.firstName << " " << family.wife.lastName << std::endl;
               std::cout << "Діти:\n";
               for (const Person& child : family.children) {
                   std::cout << child.firstName << " " << child.lastName << std::endl;
                }
                std::cout << "----------\n";
            }
        }
    }
    void getWomenWithWithTwoChildren() {
        // Знаходимо та виводимо на екран імена і прізвища всіх жінок з двома дітьми
        std::cout << "Жінки з двома дітьми:\n";
        for (const Family& family : families) {
            if (family.wife.jobInfo.employed  && family.children.size() == 2) {
                std::cout <<  family.wife.firstName << " " << family.wife.lastName << std::endl;
            }
        }
    }

    void getAllHumanData() {
        // Виводимо імена і прізвища всіх людей з БД
        std::cout << "Всі люди в базі даних:\n";
        for (const Family& family : families) {
            std::cout << "Чоловік: " << family.husband.firstName << " " << family.husband.lastName << std::endl;
            std::cout << "Дружина: " << family.wife.firstName << " " << family.wife.lastName << std::endl;
            for (const Person& child : family.children) {
                std::cout << "Дитина: " << child.firstName << " " << child.lastName << std::endl;
            }
        }
    }

    int getAllWomenWithJob() {
        // Виводимо імена і прізвища всіх дружин, що працюють
        std::cout << "Дружини, які працюють:\n";
        for (const Family& family : families) {
            if (family.wife.jobInfo.employed == true) {
                std::cout << "Дружина: " << family.wife.firstName << " " << family.wife.lastName << std::endl;
            }
        }
        return 0;
    }

    void getAllHumanWithTenYearsJob() {
        // Виводимо імена і прізвища людей, чий стаж роботи менше 10 років
        std::cout << "Люди з меншим стажем роботи (менше 10 років):\n";
        for (const Family& family : families) {
            if (family.husband.jobInfo.employed && family.husband.jobInfo.experience < 10) {
                std::cout << "Чоловік: " << family.husband.firstName << " " << family.husband.lastName << std::endl;
            }
            if (family.wife.jobInfo.employed && family.wife.jobInfo.experience < 10) {
                std::cout << "Дружина: " << family.wife.firstName << " " << family.wife.lastName << std::endl;
            }
        }
    }

    void addFamilyMember() {
        //додавання нової сім'ї
        Family newFamilyMember;
        cout << "Ім'я чоловіка: ";
        cin >> newFamilyMember.husband.firstName;
        cout << "Прізвище чоловіка: ";
        cin >> newFamilyMember.husband.lastName;
        cout << "Місяць народження: ";
        cin >> newFamilyMember.husband.birthDate.month;
        cout << "День народження: ";
        cin >> newFamilyMember.husband.birthDate.day;
        cout << "Рік народження: ";
        cin >> newFamilyMember.husband.birthDate.year;
        
        string isWorking;
        bool checker=false;
        while (checker!=true)
        {
            cout << "Має роботу? (y/n)";
            cin >> isWorking;
            if (isWorking == "y") {
                newFamilyMember.husband.jobInfo.employed = true;
                checker = true;
            }
            else if(isWorking == "n"){
                newFamilyMember.husband.jobInfo.employed = false;
                checker = true;
            }
        }
        if (newFamilyMember.husband.jobInfo.employed == true) {
            cout << "Назва професії: ";
            cin >> newFamilyMember.husband.jobInfo.profession;
            cout << "Кількість років досвіду: ";
            cin >> newFamilyMember.husband.jobInfo.experience;
        }



        cout << "Ім'я дружини: ";
        cin >> newFamilyMember.wife.firstName;
        cout << "Прізвище дружини: ";
        cin >> newFamilyMember.wife.lastName;
        cout << "Місяць народження: ";
        cin >> newFamilyMember.wife.birthDate.month;
        cout << "День народження: ";
        cin >> newFamilyMember.wife.birthDate.day;
        cout << "Рік народження: ";
        cin >> newFamilyMember.wife.birthDate.year;
        isWorking="a";
        checker = false;
        while (checker == false)
        {
            cout << "Має роботу? (y/n)";
            cin >> isWorking;
            if (isWorking == "y") {
                newFamilyMember.wife.jobInfo.employed = true;
                checker = true;
            }
            else if (isWorking == "n") {
                newFamilyMember.wife.jobInfo.employed = false;
                checker = true;
            }
        }
        if (newFamilyMember.wife.jobInfo.employed == true) {
            cout << "Назва професії: ";
            cin >> newFamilyMember.wife.jobInfo.profession;
            cout << "Кількість років досвіду: ";
            cin >> newFamilyMember.wife.jobInfo.experience;
        }




        int numOfChildren;
        cout << "Скільки дітей у цій сім'ї? ";
        cin >> numOfChildren;
        for (int i = 0; i < numOfChildren; ++i) {
            Person child;
            cout << "Ім'я дитини " << i + 1 << ": ";
            cin >> child.firstName;
            cout << "Прізвище дитини " << i + 1 << ": ";
            cin >> child.lastName;
            cout << "Місяць народження: ";
            cin >> child.birthDate.month;
            cout << "День народження: ";
            cin >> child.birthDate.day;
            cout << "Рік народження: ";
            cin >> child.birthDate.year;
            newFamilyMember.children.push_back(child);
        }
        families.push_back(newFamilyMember);
    }

int choice = 0;
int main() {

    // Створюємо родину
    Family family;

    // Додаємо інформацію про чоловіка
    family.husband.firstName = "Іван";
    family.husband.lastName = "Петров";
    family.husband.birthDate.day = 10;
    family.husband.birthDate.month = 5;
    family.husband.birthDate.year = 1980;
    family.husband.jobInfo.employed = true;
    family.husband.jobInfo.profession = "інженер";
    family.husband.jobInfo.experience = 10;

    // Додаємо інформацію про дружину
    family.wife.firstName = "Марія";
    family.wife.lastName = "Петрова";
    family.wife.birthDate.day = 15;
    family.wife.birthDate.month = 8;
    family.wife.birthDate.year = 1982;
    family.wife.jobInfo.employed = true;
    family.wife.jobInfo.profession = "вчитель";
    family.wife.jobInfo.experience = 8;

    // Додаємо інформацію про дітей
    Person child1;
    child1.firstName = "Анна";
    child1.lastName = "Петрова";
    child1.birthDate.day = 5;
    child1.birthDate.month = 2;
    child1.birthDate.year = 2005;

    Person child2;
    child2.firstName = "Петро";
    child2.lastName = "Петров";
    child2.birthDate.day = 20;
    child2.birthDate.month = 12;
    child2.birthDate.year = 2008;

    family.children.push_back(child1);
    family.children.push_back(child2);
    families.push_back(family);



    Family family1;
    // Додаємо інформацію про чоловіка
    family1.husband.firstName = "Василь";
    family1.husband.lastName = "Іванов";
    family1.husband.birthDate.day = 23;
    family1.husband.birthDate.month = 1;
    family1.husband.birthDate.year = 1990;
    family1.husband.jobInfo.employed = false;

    // Додаємо інформацію про дружину
    family1.wife.firstName = "Катерина";
    family1.wife.lastName = "Іванова";
    family1.wife.birthDate.day = 21;
    family1.wife.birthDate.month = 10;
    family1.wife.birthDate.year = 1972;
    family1.wife.jobInfo.employed = true;
    family1.wife.jobInfo.profession = "вчитель";
    family1.wife.jobInfo.experience = 15;

    // Додаємо інформацію про дітей
    Person child3;
    child3.firstName = "Галина";
    child3.lastName = "Іванова";
    child3.birthDate.day = 5;
    child3.birthDate.month = 2;
    child3.birthDate.year = 2006;

    Person child4;
    child4.firstName = "Кирило";
    child4.lastName = "Іванов";
    child4.birthDate.day = 20;
    child4.birthDate.month = 2;
    child4.birthDate.year = 2007;
    Person child5;
    child5.firstName = "Георгій";
    child5.lastName = "Іванов";
    child5.birthDate.day = 12;
    child5.birthDate.month = 7;
    child5.birthDate.year = 2008;

    family1.children.push_back(child3);
    family1.children.push_back(child4);
    family1.children.push_back(child5);

    families.push_back(family1);

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    do {
        cout << "0. Внесення цілих чисел в список\n";
        cout << "1. Перетворення рядка в список символів\n";
        cout << "2. Перетворення рядка в список атомів\n";
        cout << "3. Ввести дані для нової сім'ї\n";
        cout << "4. Вивести всі родини з двома дітьми\n";
        cout << "5. Вивести прізвища всіх жінок з двома дітьми\n";
        cout << "6. Вивести імена і прізвища всіх людей в базі даних\n";
        cout << "7. Вивести імена й прізвища всіх жінок які працюють\n";
        cout << "8. Вивести імена й прізвища людей чий стаж роботи менше 10 років\n";
        cout << "9. Вихід\n";
        std::cin >> choice;
        switch (choice){
        case 0: 
            first();
            break;
        case 1:
            second();
            break;
        case 2:third();
            break;
        case 3:addFamilyMember();
            break;
        case 4:getFamilyWithTwoChildren();
            break;
        case 5:getWomenWithWithTwoChildren();
            break;
        case 6:getAllHumanData();
            break;
        case 7:getAllWomenWithJob();
            break;
        case 8:getAllHumanWithTenYearsJob();
            break;
        default:
            break;
        }
    } while (choice!=9);

    return 0;
}
