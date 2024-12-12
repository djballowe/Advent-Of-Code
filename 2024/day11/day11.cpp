#include "iostream"
#include <cstdlib>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

void parseLine(string line, map<long, long> &stones) {
    istringstream ss(line);
    int num;

    while (ss >> num) {
        stones[num]++;
    }
    return;
}

void blink(map<long, long> &stones) {
    map<long, long> new_stones;
    for (const auto [key, val] : stones) {
        long num_count = val;
        string num_string = to_string(key);
        if (key == 0) {
            new_stones[1] += num_count;
        } else if (num_string.size() % 2 == 0) {
            long first = stol(num_string.substr(0, num_string.size() / 2));
            long second = stol(num_string.substr(num_string.size() / 2));
            new_stones[first] += num_count;
            new_stones[second] += num_count;
        } else {
            long new_key = key * 2024;
            new_stones[new_key] += num_count;
        }
    }
    stones = new_stones;
}

void day11(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    map<long, long> stones;
    long ans = 0;
    while (getline(file, line)) {
        parseLine(line, stones);
    }

    int blinks = 75;
    while (blinks) {
        blink(stones);
        blinks--;
    }

    for (const auto &[key, val] : stones) {
        ans += val;
    }

    cout << ans << endl;

    file.close();
    return;
}

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    day11(main_file);
    return 0;
}
