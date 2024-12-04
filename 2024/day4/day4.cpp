#include "iostream"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Part1

bool wordSearch(int currY, int currX, int dirx, int diry, vector<string> &grid) {
    string word = "XMAS";
    int rows = grid[0].size();
    int cols = grid.size();

    for (int i = 0; i < word.size(); i++) {
        int x = currX + i * dirx;
        int y = currY + i * diry;
        if (x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] != word[i]) {
            return false;
        }
    }

    return true;
}

void day4(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }

    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    int ans = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            for (const auto &[dirx, diry] : directions) {
                ans += wordSearch(i, j, dirx, diry, grid);
            }
        }
    }

    cout << "Part 1: " << ans << endl;

    file.close();
    return;
}
//

// Part 2
void day4Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }

    file.close();
    return;
}
//

int main() {
    string mainFile = "in.txt";
    string testFile = "in-test.txt";
    day4(mainFile);
    //    day4Part2(testFile);

    return 0;
}
