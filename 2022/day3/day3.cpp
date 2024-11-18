#include "iostream"
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

char getUniqueChar(vector<string> &group) {
    char same;
    map<char, int> charMap;
    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group[i].size(); j++) {
            char key = group[i][j];
            charMap[key]++;
            if (charMap[key] == 3) {
                same = key;
            }
        }
    }

    return same;
}

vector<string> clearDoubles(vector<string> &group) {
    map<char, int> charMap;
    vector<string> newArr;
    string newGroup = "";
    for (int i = 0; i < group.size(); i++) {
        for (int j = 0; j < group[i].size(); j++) {
            char key = group[i][j];
            if (!charMap[key]) {
                charMap[key]++;
                newGroup += key;
            }
        }
        newArr.push_back(newGroup);
        newGroup = "";
        charMap.clear();
    }
    return newArr;
}

int main() {
    fstream file("day3.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    string line;
    vector<string> group;
    int score = 0;
    while (getline(file, line)) {
        group.push_back(line);
        if (group.size() == 3) {
            vector<string> groupNoDoubles = clearDoubles(group);
            char uniqueChar = getUniqueChar(groupNoDoubles);
            group.clear();
            score += uniqueChar < 97 ? uniqueChar - 38 : uniqueChar - 96;
        }
    }
    cout << score << endl;

    file.close();
    return 0;
}
