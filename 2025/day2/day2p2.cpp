#include "../../helpers/helpers.h"
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<long long, long long>> parseRanges(std::string input) {
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<std::string> string_ranges;

    std::string seg;
    std::stringstream ss(input);

    while (std::getline(ss, seg, ',')) {
        string_ranges.push_back(seg);
    }

    ss.clear();

    for (std::string string_range : string_ranges) {
        ss.str(string_range);
        std::string first, second;
        char dash;

        if (std::getline(ss, first, '-') && ss >> second) {
            ranges.push_back({std::stol(first), std::stol(second)});
        }
        ss.clear();
    }

    return ranges;
}

int main() {
    std::string path = "../2025/day2/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    std::vector<std::pair<long long, long long>> ranges = parseRanges(input[0]);

    long long ans = 0;

    for (std::pair<long long, long long> range : ranges) {
        for (long long i = range.first; i <= range.second; i++) {
            std::string num_string = std::to_string(i);
            size_t match = false;

            size_t compare_num_idx = 0;
            std::string compare_num = {num_string[compare_num_idx]};
            size_t start = compare_num.size();
            size_t len = compare_num.size();

            while (compare_num.size() <= num_string.size() / 2) {
                std::string temp_num = num_string.substr(start, len);

                // if you get a match shift the window
                // break if youre at the end of the string
                if (compare_num == temp_num) {
                    if (start + len == num_string.size()) {
                        match = true;
                        break;
                    }
                    start += temp_num.size();
                    len = temp_num.size();
                } else {
                    // if you dont increase the size of the start num and start over
                    compare_num.push_back(num_string[++compare_num_idx]);
                    start = compare_num.size();
                    len = compare_num.size();
                    match = false;
                }
            }

            if (match) {
                std::cout << num_string << std::endl;
                ans += std::stol(num_string);
            }
        }
    }

    std::cout << ans << std::endl;
    return 0;
}
