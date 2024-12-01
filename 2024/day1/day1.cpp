#include "iostream"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void parseLines(string line, vector<int> &left, vector<int> &right) {
    istringstream stream(line);
    vector<int> numbers;
    int num;

    while (stream >> num) {
        numbers.push_back(num);
    }

    left.push_back(numbers[0]);
    right.push_back(numbers[1]);
}

void parseLinesWithFreq(string line, vector<int> &left, vector<int> &right, map<int, int> &freq) {
    istringstream stream(line);
    vector<int> numbers;
    int num;

    while (stream >> num) {
        numbers.push_back(num);
    }

    left.push_back(numbers[0]);
    right.push_back(numbers[1]);
    freq[right.back()]++;
}

void day1(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    vector<int> left;
    vector<int> right;
    int ans = 0;
    while (getline(file, line)) {
        parseLines(line, left, right);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int i = 0; i < left.size(); i++) {
        ans += abs(left[i] - right[i]);
    }

    cout << "Part 1: " << ans << endl;

    file.close();
    return;
}

void day1Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    vector<int> left;
    vector<int> right;
    map<int, int> freq;
    int ans = 0;
    while (getline(file, line)) {
        parseLinesWithFreq(line, left, right, freq);
    }

    for (int val : left) {
        if (freq[val]) {
            ans += val * freq[val];
        }
    }

    cout << "Part 2: " << ans << endl;

    file.close();
    return;
}

int main() {
    string mainFile = "in.txt";
    string testFile = "in-test.txt";
    day1(mainFile);
    day1Part2(mainFile);

    return 0;
}
