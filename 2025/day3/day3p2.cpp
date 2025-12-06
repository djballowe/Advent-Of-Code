#include "../../helpers/helpers.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string path = "../2025/day3/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    unsigned long long ans = 0;

    for (std::string bank : input) {
        std::vector<char> stack;
        int target_length = 12;
        int drops_allowed = bank.size() - target_length;

        for (char current_digit : bank) {
            while (!stack.empty() && stack.back() < current_digit && drops_allowed > 0) {
                stack.pop_back();
                drops_allowed--;
            }
            stack.push_back(current_digit);
        }

        while (stack.size() > target_length) {
            stack.pop_back();
        }

        std::string num_str = "";
        for (char digits : stack) {
            num_str += digits;
        }

        std::cout << "Found: " << num_str << std::endl;

        ans += std::stoull(num_str);
    }

    std::cout << "Total Joltage: " << ans << std::endl;
    return 0;
}
