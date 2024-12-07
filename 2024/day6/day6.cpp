#include "iostream"
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using VisitedNode = pair<pair<int, int>, pair<int, int>>;

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

void traverseGridUniqueOnly(vector<string> &grid, pair<int, int> &pos, map<pair<int, int>, int> &visited, int &unique_nodes) {
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int ptr = 0;

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
}

bool isCycle(vector<string> &grid, pair<int, int> obstruction, pair<int, int> pos, pair<int, int> start) {
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int ptr = 0;
    map<VisitedNode, int> visited;

    if (obstruction == start) {
        return false;
    }

    while (true) {
        pair<int, int> next_pos = {pos.first + directions[ptr].first, pos.second + directions[ptr].second};
        if (!inBounds(next_pos, grid)) {
            return false;
        }

        if (grid[next_pos.second][next_pos.first] == '#' || (next_pos.second == obstruction.second && next_pos.first == obstruction.first)) {
            ptr = (ptr + 1) % directions.size();
            continue;
        }

        VisitedNode cords = {pos, directions[ptr]};
        visited[cords]++;
        if (visited[cords] == 2) {
            return true;
        }

        pos = next_pos;
    }
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
    int unique_nodes = 1;
    while (getline(file, line)) {
        grid.push_back(line);
        if (pos.first == -1) {
            findStart(line, pos, j);
        }
        j++;
    }

    map<pair<int, int>, int> visited;
    traverseGridUniqueOnly(grid, pos, visited, unique_nodes);

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
    pair<int, int> start = pos;
    // same as part one but this time track the direction along with the cords

    int unique_nodes = 1;
    map<pair<int, int>, int> main_path;
    traverseGridUniqueOnly(grid, pos, main_path, unique_nodes);
    cout << unique_nodes << endl;
    int cycles = 0;

    for (const auto &[key, val] : main_path) {
        pair<int, int> obstruction = key;
        bool is_cycle = isCycle(grid, obstruction, pos, start);
        if (is_cycle) {
            cycles++;
        }
    }

    cout << cycles << endl;

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    string test2 = "in-test2.txt";
    // day6(main_file);
    day6Part2(main_file);
    // 1907 too high

    return 0;
}
