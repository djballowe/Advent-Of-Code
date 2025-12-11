#include "../../helpers/helpers.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct SplitData {
    std::vector<std::pair<long long, long long>> ranges;
};

SplitData splitInput(std::vector<std::string> &input) {
    SplitData split;
    std::vector<std::pair<long long, long long>> ranges;

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

    return {ranges};
}

int main() {
    std::string path = "../2025/day5/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);
    long long ans = 0;

    SplitData split_input = splitInput(input);

    std::sort(split_input.ranges.begin(), split_input.ranges.end());
    long long prev_end = 0;

    for (std::pair<long long, long long> ranges : split_input.ranges) {
        long long start_range = ranges.first;
        if (prev_end >= ranges.first && prev_end >= ranges.second) {
            continue;
        }
        if (prev_end >= ranges.first) {
            start_range = prev_end + 1;
        }
        ans += (ranges.second - start_range) + 1;
        prev_end = ranges.second;
    }

    std::cout << ans << std::endl;
    return 0;
}
