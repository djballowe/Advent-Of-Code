#include "iostream"
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

string getFirstHalf(string line) {
    string first = "";
    for (int i = 0; i < line.size() / 2; i++) {
        first += line[i];
    }
    return first;
}

string getSecondHalf(string line) {
    string second = "";
    for (int i = line.size() / 2; i < line.size(); i++) {
        second += line[i];
    }
    return second;
}

char getUniqueChar(string first, string second) {
    char same;
    map<char, int> charMap;
    for (int i = 0; i < first.size(); i++) {
        charMap[first[i]] += 1;
    }

    for (int i = 0; i < second.size(); i++) {
        if (charMap[second[i]]) {
            same = second[i];
            break;
        }
    }
    return same;
}

int main() {
    fstream file("day3.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    string line;
    vector<char> unique;
    int score = 0;
    while (getline(file, line)) {
        string first = getFirstHalf(line);
        string second = getSecondHalf(line);
        char same = getUniqueChar(first, second);
        score += same < 97 ? same - 38 : same - 96;
    }

    cout << score << endl;
    file.close();
    return 0;
}
