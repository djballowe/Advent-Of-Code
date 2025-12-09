#include "../../helpers/helpers.h"
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct SplitData {
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> nums;
};

SplitData splitInput(std::vector<std::string> &input) {
    SplitData split;
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> nums;

    bool range_flip = true;

    for (std::string line : input) {
        if (line == "") {
            break;
        }
        if (range_flip) {
            std::stringstream ss(line);
            std::string first, second;

            while (std::getline(ss, first, '-') && ss >> second) {
                ranges.push_back({std::stoll(first), std::stoll(second)});
            }
        }
    }

    return {ranges, nums};
}

int main() {
    std::string path = "../2025/day5/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);
    int ans = 0;

    SplitData split_input = splitInput(input);

    for (long long num : split_input.nums) {
        for (std::pair<long long, long long> range : split_input.ranges) {
            if (num >= range.first && num <= range.second) {
                ans++;
                break;
            }
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
