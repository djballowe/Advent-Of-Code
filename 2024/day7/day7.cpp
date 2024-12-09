#include "iostream"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void parseLine(string line, vector<pair<long, vector<long>>> &inputs) {
    size_t token = line.find(":");

    long first = stol(line.substr(0, token));
    string second = line.substr(token + 2);

    istringstream ss(second);
    vector<long> nums;
    long num;

    while (ss >> num) {
        nums.push_back(num);
    }

    inputs.push_back({first, nums});
    return;
}

unordered_set<long> runSolutions(unordered_set<long> &solutions, long num) {
    unordered_set<long> add_solutions;
    for (long val : solutions) {
        add_solutions.insert(val * num);
        add_solutions.insert(val + num);
    }
    return add_solutions;
}

bool isLineValid(long target, vector<long> nums) {
    if (!nums.size()) {
        return false;
    }

    if (nums.size() == 1) {
        return nums[0] == target;
    }

    unordered_set<long> solutions;
    solutions.insert(nums[0] * nums[1]);
    solutions.insert(nums[0] + nums[1]);
    for (int i = 2; i < nums.size(); i++) {
        solutions = runSolutions(solutions, nums[i]);
    }

    if (solutions.find(target) != solutions.end()) {
        return true;
    }
    return false;
}

// Part1
void day6(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    vector<pair<long, vector<long>>> inputs;
    long ans = 0;
    while (getline(file, line)) {
        parseLine(line, inputs);
    }

    // for (pair<long, vector<long>> line : inputs) {
    //     cout << line.first << ":";
    //     for (long val : line.second) {
    //         cout << val << ",";
    //     }
    //     cout << endl;
    // }

    for (pair<long, vector<long>> line : inputs) {
        bool valid = isLineValid(line.first, line.second);
        if (valid) {
            ans += line.first;
        }
    }

    cout << ans << endl;

    return;
}
//

// Part 2
void day6Part2() { return; }
//

int main() {
    string test_file = "in-test.txt";
    string main_file = "in.txt";
    day6(main_file);
    // day6Part2();

    return 0;
}
