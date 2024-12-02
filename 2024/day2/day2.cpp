#include "iostream"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool unsafeCheck(int diff, int direction) {
    return (abs(diff) > 3 || !abs(diff) || (direction < 0 && diff > 0) || (direction > 0 && diff < 0));
}

// Part1
bool isLineSafe(string line) {
    istringstream stream(line);
    int num;
    bool safe = true;
    vector<int> numbers;

    while (stream >> num) {
        numbers.push_back(num);
    }

    int direction = numbers[0] > numbers[1] ? -1 : 1;
    int j = 0;

    for (int i = 1; i < numbers.size(); i++) {
        int diff = numbers[i] - numbers[j];
        bool check = unsafeCheck(diff, direction);
        if (check) {
            safe = false;
            break;
        }
        j++;
    }

    return safe;
}

void day2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int ans = 0;
    while (getline(file, line)) {
        bool isSafe = isLineSafe(line);
        if (isSafe) {
            ans++;
        }
    }

    cout << "Part 1: " << ans << endl;

    file.close();
    return;
}

bool isLineSafeWithException(string line) {
    istringstream stream(line);
    int num;
    bool safe = true;
    vector<int> numbers;

    while (stream >> num) {
        numbers.push_back(num);
    }

    for (int i = 0; i < numbers.size(); i++) {
       // use brute force here     
    }


    return safe;
}

void day2Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int ans = 0;
    while (getline(file, line)) {
        bool isSafe = isLineSafeWithException(line);
        if (isSafe) {
            ans++;
        }
    }

    cout << "Part 2: " << ans << endl;

    file.close();
    return;
}
//

int main() {
    string mainFile = "in.txt";
    string testFile = "in-test.txt";
    // day2(mainFile);
    day2Part2(mainFile);
    // 552 too high
    // 508 too low

    return 0;
}
