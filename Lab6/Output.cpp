#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
#include "Converter.cpp"

namespace Lab6 {
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
            NodesFormat(Lab6::FormChanger::ToNodes(incMatrix));

            // Виведення списку суміжності з матриці суміжності
            AdjListFormat(Lab6::FormChanger::ToAdjList(adjMatrix));
        }

    public:
        // Метод для форматування та виведення графу, заданого матрицею суміжності
        static void AdjGraphFormat(const std::vector<std::vector<signed char>>& adjMatrix, const std::string& header) {
            std::vector<std::vector<signed char>> incMatrix = Lab6::FormChanger::ToInc(adjMatrix);
            GraphFormat(adjMatrix, incMatrix, header);
        }

        // Метод для форматування та виведення графу, заданого матрицею включення
        static void IncGraphFormat(const std::vector<std::vector<signed char>>& incMatrix, const std::string& header) {
            std::vector<std::vector<signed char>> adjMatrix = Lab6::FormChanger::ToAdj(incMatrix);
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
}
