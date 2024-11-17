#include "iostream"
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    map<char, int> charMap = {{'X', 1}, {'Y', 2}, {'Z', 3}};
    map<char, int> points = {{'X', 0}, {'Y', 3}, {'Z', 6}};
    map<char, vector<map<char, char>>> winLossMap;

    winLossMap['X'] = {{{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}}};
    winLossMap['Y'] = {{{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}}};
    winLossMap['Z'] = {{{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}}};

    fstream file("day2.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    string line;
    int score = 0;
    while (getline(file, line)) {
        vector<map<char, char>> playKeys = winLossMap[line[2]];
        char key;
        for (int i = 0; i < playKeys.size(); i++) {
            if (playKeys[i][line[0]]) {
                key = playKeys[i][line[0]];
            }
        }
        score += charMap[key] + points[line[2]];
    }

    cout << score << endl;

    file.close();
    return 0;
}

// A Y
// B X
// C Z
