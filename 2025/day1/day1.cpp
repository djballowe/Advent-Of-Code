#include "../../helpers/helpers.h"
#include <iostream>
#include <string>

int parseInstructions(std::string line) {
    char direction = line[0];
    std::string number;

    for (int i = 1; i < line.size(); i++) {
        number.push_back(line[i]);
    }

    int number_direction = direction == 'L' ? (std::stoi(number) * -1) : std::stoi(number);

    return number_direction;
}

int main() {
    std::string path = "../2025/day1/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);
    int tick = 50;
    int ans = 0;

    for (std::string line : input) {
        tick += parseInstructions(line);
        if (tick > 99 || tick < 0) {
            tick = tick % 100;
        }
        ans += tick == 0 ? 1 : 0;
    }

    std::cout << "answer is: " << ans << std::endl;

    return 0;
}

// 459 to low
