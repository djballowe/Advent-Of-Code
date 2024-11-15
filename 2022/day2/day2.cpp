#include "iostream"
#include <fstream>
#include <map>
#include <string>

using namespace std;

map<char, int> charMap = {{'X', 1}, {'Y', 2}, {'Z', 3}};
map<string, int> winCombos = {{"A X", 3}, {"A Y", 6}, {"A Z", 0},
                              {"B X", 0}, {"B Y", 3}, {"B Z", 6},
                              {"C X", 6}, {"C Y", 0}, {"C Z", 3}};

int main() {
    fstream file("day2.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    string line;
    int score = 0;
    while (getline(file, line)) {
        score += charMap[line[2]] + winCombos[line];
    }

    cout << score << endl;

    file.close();
    return 0;
}
