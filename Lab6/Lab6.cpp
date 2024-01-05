#include <iostream>
#include <locale>
#include <clocale>
#include <vector>
#include <unordered_map>
#include <iomanip>

class FormChanger {
public:
    static std::vector<std::vector<signed char>> ToAdj(const std::vector<std::vector<signed char>>& inc) {
        int height = inc.size();
        int width = inc[0].size();
        std::vector<std::vector<signed char>> adj(height, std::vector<signed char>(height, 0));

        for (int x = 0; x < width; ++x) {
            std::tuple<signed char, signed char> nodes[2];
            bool hasSecond = false;

            for (int y = 0; y < height; ++y) {
                if (inc[y][x] != 0) {
                    if (inc[y][x] == 2) {
                        adj[y][y] = 1;
                        break;
                    }
                    else {
                        if (hasSecond) {
                            nodes[0] = std::make_tuple(static_cast<signed char>(y), inc[y][x]);

                            if (std::get<1>(nodes[0]) > std::get<1>(nodes[1]))
                                std::swap(nodes[0], nodes[1]);

                            adj[std::get<0>(nodes[1])][std::get<0>(nodes[0])] = 1;

                            if (std::get<1>(nodes[0]) == 1)
                                adj[std::get<0>(nodes[0])][std::get<0>(nodes[1])] = 1;
                        }
                        else {
                            nodes[1] = std::make_tuple(static_cast<signed char>(y), inc[y][x]);
                            hasSecond = true;
                        }
                    }
                }
            }
        }

        return adj;
    }

    static std::vector<std::vector<signed char>> ToInc(const std::vector<std::vector<signed char>>& adj) {
        int size = adj.size();
        std::vector<std::vector<signed char>> copy(size, std::vector<signed char>(size, 0));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                copy[i][j] = adj[i][j];
            }
        }

        std::vector<std::vector<signed char>> inc;

        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                if (copy[y][x] == 1) {
                    inc.push_back(std::vector<signed char>(size, 0));

                    if (x == y) {
                        inc.back()[x] = 2;
                    }
                    else {
                        inc.back()[x] = 1;

                        if (copy[x][y] == 1) {
                            inc.back()[y] = 1;
                            copy[x][y] = 0;
                        }
                        else {
                            inc.back()[y] = -1;
                        }
                    }
                }
            }
        }

        return inc;
    }

    static std::vector<std::tuple<signed char, signed char>> ToNodes(const std::vector<std::vector<signed char>>& inc) {
        int height = inc.size();
        int width = inc[0].size();
        std::vector<std::tuple<signed char, signed char>> nodes(width);

        for (int x = 0; x < width; ++x) {
            bool hasFirst = false;

            for (int y = 0; y < height; ++y) {
                if (inc[y][x] != 0) {
                    if (inc[y][x] == 2) {
                        nodes[x] = std::make_tuple(static_cast<signed char>(y), static_cast<signed char>(y));
                    }
                    else if (hasFirst) {
                        std::get<1>(nodes[x]) = static_cast<signed char>(y);

                        if (std::get<0>(nodes[x]) > std::get<1>(nodes[x])) {
                            std::swap(std::get<0>(nodes[x]), std::get<1>(nodes[x]));
                        }
                    }
                    else {
                        nodes[x] = std::make_tuple(static_cast<signed char>(y), static_cast<signed char>(0));
                        hasFirst = true;
                    }
                }
            }
        }

        return nodes;
    }

    static std::unordered_map<signed char, std::vector<signed char>> ToAdjList(const std::vector<std::vector<signed char>>& matrix) {
        int size = matrix.size();
        std::unordered_map<signed char, std::vector<signed char>> list;
        std::vector<signed char> nodes;

        for (int x = 0; x < size; ++x) {
            nodes.clear();

            for (int y = 0; y < size; ++y) {
                if (matrix[y][x] != 0) {
                    nodes.push_back(static_cast<signed char>(y));
                }
            }

            if (!nodes.empty()) {
                list[static_cast<signed char>(x)] = nodes;
            }
        }

        return list;
    }
};


class Output {
private:
    static void GraphFormat(const std::vector<std::vector<signed char>>& adjMatrix,
        const std::vector<std::vector<signed char>>& incMatrix,
        const std::string& header) {
        std::cout << "\n" << header << "\n";

        // Виведення матриці суміжності
        AdjFormat(adjMatrix);

        // Виведення матриці включення
        IncFormat(incMatrix);

        // Виведення списку вузлів з матриці включення
        NodesFormat(FormChanger::ToNodes(incMatrix));

        // Виведення списку суміжності з матриці суміжності
        AdjListFormat(FormChanger::ToAdjList(adjMatrix));
    }

public:
    // Метод для форматування та виведення графу, заданого матрицею суміжності
    static void AdjGraphFormat(const std::vector<std::vector<signed char>>& adjMatrix, const std::string& header) {
        std::vector<std::vector<signed char>> incMatrix = FormChanger::ToInc(adjMatrix);
        GraphFormat(adjMatrix, incMatrix, header);
    }

    // Метод для форматування та виведення графу, заданого матрицею включення
    static void IncGraphFormat(const std::vector<std::vector<signed char>>& incMatrix, const std::string& header) {
        std::vector<std::vector<signed char>> adjMatrix = FormChanger::ToAdj(incMatrix);
        GraphFormat(adjMatrix, incMatrix, header);
    }

    // Метод для виведення матриці суміжності
    static void AdjFormat(const std::vector<std::vector<signed char>>& matrix) {
        int rows = matrix.size();
        int columns = matrix[0].size();

        std::cout << "\\ | ";
        for (int j = 0; j < columns; j++) std::cout << (char)('a' + j) << " ";
        std::cout << "\n" << std::string((columns + 2) * 2 - 1, '-') << "\n";

        for (int i = 0; i < rows; i++) {
            std::cout << (char)('a' + i) << " | ";
            for (int j = 0; j < columns; j++) std::cout << static_cast<int>(matrix[i][j]) << " ";
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    // Метод для виведення матриці включення
    static void IncFormat(const std::vector<std::vector<signed char>>& matrix) {
        int rows = matrix.size();
        int columns = matrix[0].size();

        std::cout << "\\ |";
        for (int j = 0; j < columns; j++) std::cout << std::setw(3) << (j + 1);
        std::cout << "\n" << std::string((columns + 1) * 3, '-') << "\n";

        for (int i = 0; i < rows; i++) {
            std::cout << (char)('a' + i) << " |";
            for (int j = 0; j < columns; j++) std::cout << std::setw(3) << static_cast<int>(matrix[i][j]);
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    // Метод для виведення списку вузлів
    static void NodesFormat(const std::vector<std::tuple<signed char, signed char>>& list) {
        for (const auto& t : list) {
            std::cout << "(" << (char)('A' + std::get<0>(t)) << ", " << (char)('A' + std::get<1>(t)) << ") ";
        }
        std::cout << "\n\n";
    }

    // Метод для виведення списку суміжності
    static void AdjListFormat(const std::unordered_map<signed char, std::vector<signed char>>& list) {
        for (const auto& item : list) {
            std::cout << (char)('A' + item.first) << " → {";
            for (const auto& num : item.second) {
                std::cout << (char)('A' + num) << ", ";
            }
            std::cout << "}\n";
        }
        std::cout << "\n";
    }
};

class Input {
public:
    static std::vector<std::vector<signed char>> AdjMatrix() {
        std::cout << "Кількість вершин: ";
        int size;
        std::cin >> size;

        std::vector<std::vector<signed char>> matrix(size, std::vector<signed char>(size));

        std::cout << "Введіть елементи " << size << "x" << size << " рядок за рядком:" << std::endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cin >> matrix[i][j];
            }
        }

        return matrix;
    }

    static std::vector<std::vector<signed char>> IncMatrix() {
        std::cout << "Кількість вершин: ";
        int height;
        std::cin >> height;

        std::cout << "Кількість ребер: ";
        int width;
        std::cin >> width;

        std::vector<std::vector<signed char>> matrix(height, std::vector<signed char>(width));

        std::cout << "Введіть елементи " << height << "x" << width << " рядок за рядком:" << std::endl;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                std::cin >> matrix[i][j];
            }
        }

        return matrix;
    }
};

class Creator {
public:
    static std::vector<std::vector<signed char>> InputAdjMatrix(int size, bool mirror, const std::vector<std::pair<char, char>>& edges) {
        std::vector<std::vector<signed char>> matrix(size, std::vector<signed char>(size, 0));

        for (const auto& edge : edges) {
            char y = edge.first;
            char x = edge.second;

            // Встановлення зв'язку між вершинами
            matrix[y - 'a'][x - 'a'] = 1;

            // Якщо потрібно, встановлення зворотнього зв'язку
            if (mirror)
                matrix[x - 'a'][y - 'a'] = 1;
        }

        return matrix;
    }

    static void Display() {
        // Створення та виведення ненапрямленого графа
        Output::AdjFormat(InputAdjMatrix(8, true, {
            { 'a', 'b'}, { 'a', 'e' }, { 'a', 'f' },
            { 'b', 'a' }, { 'b', 'e' }, { 'b', 'd' },
            { 'c', 'a' }, { 'c', 'f' },
            { 'd', 'd' }, { 'd', 'f' }, { 'd', 'g' },
            { 'e', 'a' }, { 'e', 'b' }, { 'e', 'f' },
            { 'f', 'c' }, { 'f', 'd' }, { 'f', 'e' }, { 'f', 'g' }
            }));

        // Створення та виведення напрямленого графа
        Output::AdjFormat(InputAdjMatrix(8, false, {
            { 'a', 'a'}, {'a', 'b'}, {'a', 'b'},
            { 'b', 'd' },
            { 'c', 'c' }, { 'c', 'f' },
            { 'd', 'h' },
            { 'e', 'h' },
            { 'f', 'h' }
            }));
    }
};

int main() {
	setlocale(LC_ALL, "ukr");
	std::wcout.imbue(std::locale(""));

    char value;
    std::cout << "Виберіть дію:\n"
        "1. Вивести на еран всі представлення заданих графів\n"
        "2. Вивести на екран всі пердставелння графа на основі введеної матриці суміжності\n"
        "3. Вивести на екран всі пердставелння графа на основі введеної матриці інцидентності\n";
    std::cin >> value;

    switch (value) {
    case '1':
        Creator::Display();
        break;
    case '2':
        Output::AdjGraphFormat(Input::AdjMatrix(), "Представлення графа:");
        break;
    case '3':
        Output::IncGraphFormat(Input::IncMatrix(), "Представлення графа:");
        break;
    default:
        std::cout << "Невірний вибір. Спробуйте ще раз.\n";
    }
}