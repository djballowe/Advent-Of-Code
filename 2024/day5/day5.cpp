#include "iostream"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Part1
void parseOrder(string line, map<int, vector<int>> &order) {
    char split = line.find("|");
    pair<int, int> nums = {stoi(line.substr(0, split)), stoi(line.substr(split + 1))};

    order[nums.first].push_back(nums.second);
}

void parseLines(string line, vector<vector<int>> &num_lines) {
    stringstream ss(line);
    string token;
    vector<int> nums;

    while (getline(ss, token, ',')) {
        nums.push_back(stoi(token));
    }
    num_lines.push_back(nums);
}

bool check(int curr_num, int adjacent, vector<int> &order) {
    bool found = false;
    for (int num : order) {
        if (adjacent == num) {
            found = true;
        }
    }
    return found;
}

void day5(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    map<int, vector<int>> order;
    vector<vector<int>> num_lines;
    bool section = true;
    while (getline(file, line)) {
        if (line == "") {
            section = false;
        } else {
            section ? parseOrder(line, order) : parseLines(line, num_lines);
        }
    }

    int ans = 0;
    for (int i = 0; i < num_lines.size(); i++) {
        int middle = num_lines[i][num_lines[i].size() / 2];
        int j = 0;
        int k = 1;
        bool is_valid = true;
        while (k < num_lines[i].size()) {
            int curr_num = num_lines[i][j];
            int adjacent = num_lines[i][k];
            is_valid = check(curr_num, adjacent, order[curr_num]);
            if (!is_valid) {
                break;
            }
            j++;
            k++;
        }
        ans += is_valid ? middle : 0;
    }

    cout << "Part 1: " << ans << endl;

    file.close();
    return;
}
//

// Part 2
void day5Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    map<int, vector<int>> order;
    vector<vector<int>> num_lines;
    bool section = true;
    while (getline(file, line)) {
        if (line == "") {
            section = false;
        } else {
            section ? parseOrder(line, order) : parseLines(line, num_lines);
        }
    }

    int ans = 0;
    for (int i = 0; i < num_lines.size(); i++) {
        vector<int> &lines = num_lines[i];
        vector<int> compare = num_lines[i];

        // custom sort lambda
        sort(lines.begin(), lines.end(), [&order](int a, int b) {
            vector<int> rules = order[a];
            for (int val : rules) {
                if (b == val) {
                    return true;
                }
            }
            return false;
        });

        if (lines != compare) {
            int middle = lines[lines.size() / 2];
            ans += middle;
        }
    }

    cout << "Part 2: " << ans << endl;

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    string test2 = "in-test2.txt";
    day5(main_file);
    day5Part2(main_file);

    return 0;
}
