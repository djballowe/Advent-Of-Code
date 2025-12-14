#include "../../helpers/helpers.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::optional<std::pair<int, int>> checkNode(size_t i, size_t j, std::vector<std::string> &input, int &ans) {
    while (i < input.size() - 1) {
        if (input[i][j] == '^') {
            input[i][j] = '*';
            ans++;
            return {{i, j}};
        } else if (input[i][j] == '*') {
            break;
        }
        i++;
    }
    return std::nullopt;
}

std::pair<int, int> findStart(std::vector<std::string> &input) {
    int start = input[0].find('S');
    int i = 0;
    int j = start;

    while (input[i][j] != '^') {
        i++;
    }

    input[i][j] = '*';
    return {i, j};
}

int main() {
    std::string path = "../2025/day7/in-test.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    int ans = 0;
    int i = 0;
    int j = 0;

    std::pair<int, int> start = findStart(input);

    std::vector<std::pair<int, int>> start_points = {start};

    while (start_points.size()) {
        i = start_points.back().first;
        j = start_points.back().second;
        start_points.pop_back();
        std::optional<std::pair<int, int>> right_node = checkNode(i, j + 1, input, ans);
        std::optional<std::pair<int, int>> left_node = checkNode(i, j - 1, input, ans);
        if (right_node) {
            start_points.push_back(*right_node);
        }
        if (left_node) {
            start_points.push_back(*left_node);
        }
    }

    for (std::string line : input) {
        std::cout << line << std::endl;
    }

    std::cout << ans << std::endl;

    return 0;
}
