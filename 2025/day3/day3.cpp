#include "../../helpers/helpers.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string path = "../2025/day3/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    int ans = 0;

    for (std::string banks : input) {
        int first = 0;
        int max = 0;

        for (int i = 0; i < banks.size(); i++) {
            int bat = banks[i] - '0';
            if (bat > first) {
                first = bat;
                for (int j = i + 1; j < banks.size(); j++) {
                    std::string string_num = std::to_string(first) + banks[j];
                    max = std::max(std::stoi(string_num), max);
                }
            }
        }
        ans += max;
    }
    std::cout << ans << std::endl;
    return 0;
}
