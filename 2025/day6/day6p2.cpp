#include "../../helpers/helpers.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string path = "../2025/day6/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);
    std::string opperators = input[input.size() - 1];
    input.pop_back();

    int i = 0;
    int j = 0;
    long long curr_problem = 0;
    long long ans = 0;
    char op = opperators[j];
    std::string curr_num = "";

    while (true) {
        if (opperators[j] != ' ') {
            op = opperators[j];
        }
        char num = input[i][j];
        if (num != ' ') {
            curr_num += num;
        }
        if (i == input.size() - 1) {
            if (curr_num != "") {
                int int_num = std::stoi(curr_num);
                if (op == '*') {
                    curr_problem = curr_problem == 0 ? curr_problem = int_num : curr_problem *= int_num;
                } else {
                    curr_problem += int_num;
                }
            } else if (curr_num == "") {
                ans += curr_problem;
                curr_problem = 0;
            }
            if (j == input[i].size() - 1) {
                ans += curr_problem;
                break;
            }
            i = 0;
            j++;
            curr_num = "";
        } else {
            i++;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}
