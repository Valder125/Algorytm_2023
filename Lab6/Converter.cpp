#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

namespace Lab6 {
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
}
