#include "../../helpers/helpers.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> parseNumbers(std::vector<std::string> &input) {
    std::vector<std::vector<int>> lines;
    std::vector<int> numbers;
    int temp;

    for (int i = 0; i < input.size() - 1; i++) {
        std::stringstream ss(input[i]);
        while (ss >> temp) {
            numbers.push_back(temp);
        }
        lines.push_back(numbers);
        numbers.clear();
    }

    return lines;
}

std::vector<char> parseOperators(std::string operator_line) {
    std::vector<char> operators;

    for (char op : operator_line) {
        if (op == '*' || op == '+') {
            operators.push_back(op);
        }
    }

    return operators;
}

int main() {
    std::string path = "../2025/day6/in.txt";
    std::vector<std::string> input = AdventHelpers::parseLines(path);

    std::vector<std::vector<int>> parsed_input = parseNumbers(input);
    std::vector<char> parsed_operators = parseOperators(input[input.size() - 1]);

    int i = 0;
    int j = 0;
    long long curr_problem = 0;
    long long ans = 0;

    while (true) {
        char op = parsed_operators[j];
        int num = parsed_input[i][j];
        if (op == '*') {
            curr_problem = curr_problem == 0 ? curr_problem = num : curr_problem *= num;
        } else {
            curr_problem += num;
        }

        if (i == parsed_input.size() - 1) {
            ans += curr_problem;
            if (j == parsed_input[i].size() - 1) {
                break;
            }
            i = 0;
            j++;
            curr_problem = 0;
        } else {
            i++;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}
