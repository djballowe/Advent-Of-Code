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

// Part 2
vector<int> convertLine(string line) {
    istringstream stream(line);
    int num;
    vector<int> numbers;

    while (stream >> num) {
        numbers.push_back(num);
    }

    return numbers;
}

bool checkLine(vector<int> nums) {
    int direction = nums[0] > nums[1] ? -1 : 1;
    int j = 0;

    for (int i = 1; i < nums.size(); i++) {
        int diff = nums[i] - nums[j];
        bool check = unsafeCheck(diff, direction);
        if (check) {
            return false;
        }
        j++;
    }
    return true;
}

bool isLineSafeWithException(vector<int> nums) {
    int ignore = 0;
    size_t numsSize = nums.size();
    bool firstPass = checkLine(nums);
    if (firstPass) {
        return true;
    }
    for (int i = 0; i < numsSize; i++) {
        vector<int> copy = nums;
        copy.erase(copy.begin() + ignore);
        bool check = checkLine(copy);
        if (check) {
            return true;
        }
        ignore++;
    }

    return false;
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
        vector<int> nums = convertLine(line);
        bool isSafe = isLineSafeWithException(nums);
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
    day2(mainFile);
    day2Part2(mainFile);

    return 0;
}
