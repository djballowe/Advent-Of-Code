#include "iostream"
#include <cstdlib>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void findAntennas(string line, int y, map<char, vector<pair<int, int>>> &antennas) {
    for (int x = 0; x < line.size(); x++) {
        if (line[x] != '.') {
            pair<int, int> cords = {x, y};
            antennas[line[x]].push_back(cords);
        }
    }
}

void day8(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    map<char, vector<pair<int, int>>> antennas;
    vector<string> grid;
    while (getline(file, line)) {
        grid.push_back(line);
    }

    for (int i = 0; i < grid.size(); i++) {
        findAntennas(grid[i], i, antennas);
    }

    int cols = grid.size();
    int rows = grid[0].size();

    int count = 0;

    set<pair<int, int>> antinodes;
    for (const auto &[key, val] : antennas) {
        int j = 0;
        while (j < val.size()) {
            antinodes.insert(val[j]);
            for (int i = j + 1; i < val.size(); i++) {
                antinodes.insert(val[i]);
                int diffX = val[j].first - val[i].first;
                int diffY = val[j].second - val[i].second;

                int antinode_plusX = val[i].first - diffX;
                int antinode_plusY = val[i].second - diffY;
                int antinode_minusX = val[j].first + diffX;
                int antinode_minusY = val[j].second + diffY;

                pair<int, int> antinode_plus = {antinode_plusX, antinode_plusY};
                pair<int, int> antinode_minus = {antinode_minusX, antinode_minusY};

                while (antinode_plus.first < rows && antinode_plus.first >= 0 && antinode_plus.second < cols && antinode_plus.second >= 0) {
                    antinodes.insert(antinode_plus);
                    antinode_plusX -= diffX;
                    antinode_plusY -= diffY;
                    antinode_plus = {antinode_plusX, antinode_plusY};
                }

                while (antinode_minus.first < rows && antinode_minus.first >= 0 && antinode_minus.second < cols && antinode_minus.second >= 0) {
                    antinodes.insert(antinode_minus);
                    antinode_minusX += diffX;
                    antinode_minusY += diffY;
                    antinode_minus = {antinode_minusX, antinode_minusY};
                }
            }
            j++;
        }
    }

    file.close();
    return;
}
//

// Part 2
void day5Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    while (getline(file, line)) {
    }

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    day8(main_file);
    // 393 too high

    return 0;
}
