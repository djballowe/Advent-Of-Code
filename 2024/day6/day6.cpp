#include "iostream"
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void findStart(string line, pair<int, int> &start, int j) {
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '^') {
            start.first = i;
            start.second = j;
            break;
        }
    }
}

bool inBounds(pair<int, int> pos, vector<string> &grid) {
    int x = grid[0].size();
    int y = grid.size();

    if (pos.first < 0 || pos.first >= x || pos.second < 0 || pos.second >= y) {
        return false;
    }
    return true;
}

// Part1
void day6(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    vector<string> grid;
    pair<int, int> pos = {-1, -1};
    int j = 0;
    while (getline(file, line)) {
        grid.push_back(line);
        if (pos.first == -1) {
            findStart(line, pos, j);
        }
        j++;
    }

    map<pair<int, int>, int> visited;
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int ptr = 0;
    int unique_nodes = 1;

    while (true) {
        pair<int, int> next_pos = {pos.first + directions[ptr].first, pos.second + directions[ptr].second};
        if (!inBounds(next_pos, grid)) {
            break;
        }

        if (grid[next_pos.second][next_pos.first] == '#') {
            ptr = (ptr + 1) % directions.size();
            continue;
        }

        if (visited.emplace(pos, 1).second) {
            unique_nodes++;
        }

        pos = next_pos;
    }

    cout << "Part 1: " << unique_nodes << endl;

    file.close();
    return;
}
//

// Part 2
void day6Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    // run the path as normal from part 1
    // iterate through unique nodes places a new blocker on one coordinate
    // run the path again
    // if you hit the new blocker more than once you are in a loop

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
    string test2 = "in-test2.txt";
    day6(main_file);
    // day6Part2(main_file);

    return 0;
}
