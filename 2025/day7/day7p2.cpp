#include "../../helpers/helpers.h"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

std::optional<std::pair<int, int>> checkNode(size_t i, size_t j, std::vector<std::string> &input, int &ans) {
    while (i < input.size() - 1) {
        if (input[i][j] == '^') {
            return {{i, j}};
        }
        i++;
    }
    ans++;
    return std::nullopt;
}

std::pair<int, int> findStart(std::vector<std::string> &input) {
    int start = input[0].find('S');
    int i = 0;
    int j = start;

    while (input[i][j] != '^') {
        i++;
    }

    return {i, j};
}

int main() {
    std::string path = "../2025/day7/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    int ans = 1;
    int i = 0;
    int j = 0;

    std::pair<int, int> start = findStart(input);

    std::vector<std::pair<int, int>> stack = {start};

    while (stack.size()) {
        i = stack.back().first;
        j = stack.back().second;
        stack.pop_back();
        std::optional<std::pair<int, int>> right_node = checkNode(i, j + 1, input, ans);
        std::optional<std::pair<int, int>> left_node = checkNode(i, j - 1, input, ans);
        if (right_node) {
            stack.push_back(*right_node);
        }
        if (left_node) {
            stack.push_back(*left_node);
        }
        std::cout << stack.size() << std::endl;
    }

    for (std::string line : input) {
        std::cout << line << std::endl;
    }

    std::cout << ans << std::endl;

    return 0;
}
