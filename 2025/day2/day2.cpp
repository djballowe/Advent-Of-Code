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
            // this is not needed but fuck it 100ms faster
            if (first.size() % 2 != 0 && second.size() % 2 != 0) {
                ss.clear();
                continue;
            }
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

    std::vector<long long> ids;

    for (std::pair<long long, long long> range : ranges) {
        for (long long i = range.first; i <= range.second; i++) {
            std::string num_string = std::to_string(i);
            if (num_string.size() % 2 == 0) {
                size_t mid = num_string.size() / 2;
                std::string a = num_string.substr(0, mid);
                std::string b = num_string.substr(mid, num_string.size());
                if (a == b) {
                    ids.push_back(std::stol(a + b));
                }
            }
        }
    }
    long long ans = 0;
    for (long long id : ids) {
        ans += id;
    }

    std::cout << ans << std::endl;
    return 0;
}
