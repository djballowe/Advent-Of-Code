#include "iostream"
#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

// Part1
int parseLinePart1(string line) {
    regex pattern(R"(mul\((\d+),(\d+)\))");
    smatch matches;

    auto ptr = sregex_iterator(line.begin(), line.end(), pattern);
    auto end = sregex_iterator();

    int acc = 0;

    while (ptr != end) {
        smatch match = *ptr++;
        acc += stoi(match[1]) * stoi(match[2]);
    }

    return acc;
}

void day3(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int ans = 0;
    while (getline(file, line)) {
        ans += parseLinePart1(line);
    }

    cout << "Part 1: " << ans << endl;

    file.close();
    return;
}
//

// Part 2
int parseLinePart2(string line) {
    regex pattern(R"(mul\((\d+),(\d+)\))");
    smatch matches;

    auto ptr = sregex_iterator(line.begin(), line.end(), pattern);
    auto end = sregex_iterator();

    int acc = 0;

    while (ptr != end) {
        smatch match = *ptr++;
        int val = stoi(match[1]) * stoi(match[2]);
    }

    return acc;
}

void day3Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int ans = 0;
    while (getline(file, line)) {
        ans += parseLinePart2(line);
    }

    cout << "Part 2: " << ans << endl;

    file.close();
    return;
}
//

int main() {
    string mainFile = "in.txt";
    string testFile = "in-test.txt";
    //    day3(mainFile);
    day3Part2(testFile);

    return 0;
}
