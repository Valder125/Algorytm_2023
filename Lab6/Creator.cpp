#include <iostream>
#include <vector>

namespace Lab6 {
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
            InputAdjMatrix(8, true, {
                { 'a', 'b'}, { 'a', 'e' }, { 'a', 'f' },
                { 'b', 'a' }, { 'b', 'e' }, { 'b', 'd' },
                { 'c', 'a' }, { 'c', 'f' }, 
                { 'd', 'd' }, { 'd', 'f' }, { 'd', 'g' },
                { 'e', 'a' }, { 'e', 'b' }, { 'e', 'f' },
                { 'f', 'c' }, { 'f', 'd' }, { 'f', 'e' }, { 'f', 'g' }
                });

            // Створення та виведення напрямленого графа
            InputAdjMatrix(8, false, {
                { 'a', 'a'}, {'a', 'b'}, {'a', 'b'},
                { 'b', 'd' },
                { 'c', 'c' }, { 'c', 'f' }, 
                { 'd', 'h' },
                { 'e', 'h' },
                { 'f', 'h' }
                });
        }
    };
}