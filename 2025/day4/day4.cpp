#include "../../helpers/helpers.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::string path = "../2025/day4/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);
    std::vector<std::pair<int, int>> positions = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

    int ans = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '@') {
                std::pair current_pos = {i, j};
                int roll_count = 0;
                for (int cords = 0; cords < positions.size(); cords++) {
                    int newI = current_pos.first + positions[cords].first;
                    int newJ = current_pos.second + positions[cords].second;

                    if (newI >= 0 && newJ >= 0 && newI < input.size() && newJ < input[i].size()) {
                        char symbol = input[newI][newJ];
                        if (symbol == '@') {
                            roll_count++;
                        }
                    }
                }
                ans += roll_count < 4 ? 1 : 0;
            }
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
