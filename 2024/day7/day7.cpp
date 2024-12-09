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
        add_solutions.insert(stol(to_string(val) + to_string(num)));
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
    solutions.insert(stol(to_string(nums[0]) + to_string(nums[1])));
    for (int i = 2; i < nums.size(); i++) {
        solutions = runSolutions(solutions, nums[i]);
    }

    if (solutions.find(target) != solutions.end()) {
        return true;
    }
    return false;
}

void day7(string path) {
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

    for (pair<long, vector<long>> line : inputs) {
        bool valid = isLineValid(line.first, line.second);
        if (valid) {
            ans += line.first;
        }
    }

    cout << ans << endl;

    return;
}

int main() {
    string test_file = "in-test.txt";
    string main_file = "in.txt";
    day7(main_file);

    return 0;
}
