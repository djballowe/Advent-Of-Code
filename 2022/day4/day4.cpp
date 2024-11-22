#include "iostream"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> getNumbers(string line) {
    vector<int> numbers;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        stringstream rangeStream(token);
        string number;
        while (getline(rangeStream, number, '-')) {
            numbers.push_back(stoi(number));
        }
    }
    return numbers;
}

int main() {
    fstream file("day4.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    int count = 0;
    string line;
    while (getline(file, line)) {
        vector<int> numbers = getNumbers(line);
        int startOf1 = numbers[0];
        int startOf2 = numbers[2];
        int endOf1 = numbers[1];
        int endOf2 = numbers[3];
        if ((startOf2 <= endOf1 && endOf2 >= endOf1) ||
            (startOf1 <= endOf2 && endOf1 >= endOf2)) {
            count++;
        }
    }

    cout << count << endl;

    file.close();
    return 0;
}

// 3456
//   5678

// 3456
// 234
