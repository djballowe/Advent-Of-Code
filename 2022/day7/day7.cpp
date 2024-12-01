#include "iostream"
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void parseCommand(vector<char> &curr_dirs, string line) {
    string command = string(1, line[2]) + line[3];
    switch {
        case "cd":
            
    }
}

void day6Part1(string path) {
    map<char, int> char_count;
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int sum = 0;

    vector<char> curr_dirs;
    while (getline(file, line)) {
        if (line[0] == '$') {
            parseCommand(curr_dirs, line);
        }
    }

    file.close();
    return;
}

int main() {
    string mainFile = "day6.txt";
    string testFile = "day6-test.txt";
    day6Part1(mainFile);

    return 0;
}
