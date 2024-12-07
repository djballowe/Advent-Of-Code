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

void traverseGridUniqueOnly(vector<string> &grid, pair<int, int> pos, map<pair<int, int>, int> &visited) {
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int ptr = 0;

    while (true) {
        pair<int, int> next_pos = {pos.first + directions[ptr].first, pos.second + directions[ptr].second};
        if (!inBounds(next_pos, grid)) {
            visited[pos]++;
            break;
        }

        if (grid[next_pos.second][next_pos.first] == '#') {
            ptr = (ptr + 1) % directions.size();
            continue;
        }

        visited.emplace(pos, 1);

        pos = next_pos;
    }
}

bool isCycle(vector<string> &grid, pair<int, int> obstruction, pair<int, int> pos) {
    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    int ptr = 0;
    map<VisitedNode, int> visited;

    while (true) {
        pair<int, int> next_pos = {pos.first + directions[ptr].first, pos.second + directions[ptr].second};
        if (!inBounds(next_pos, grid)) {
            return false;
        }

        if (grid[next_pos.second][next_pos.first] == '#' || (next_pos.second == obstruction.second && next_pos.first == obstruction.first)) {
            ptr = (ptr + 1) % directions.size();
            continue;
        }

        // if I ever hit a node that has both the same cords and direction Im in an infinite loop
        VisitedNode cords = {pos, directions[ptr]};
        visited[cords]++;
        if (visited[cords] == 2) {
            return true;
        }

        pos = next_pos;
    }
}

// Part1
void day6(vector<string> grid, pair<int, int> pos) {
    map<pair<int, int>, int> visited;
    traverseGridUniqueOnly(grid, pos, visited);

    cout << "Part 1: " << visited.size() << endl;

    return;
}
//

// Part 2
void day6Part2(vector<string> grid, pair<int, int> pos) {
    // same as part one but this time track the direction along with the cords
    map<pair<int, int>, int> main_path;
    traverseGridUniqueOnly(grid, pos, main_path);
    int cycles = 0;

    for (const auto &[key, val] : main_path) {
        pair<int, int> obstruction = key;
        bool is_cycle = isCycle(grid, obstruction, pos);
        if (is_cycle) {
            cycles++;
        }
    }

    cout << "Part 2: " << cycles << endl;
    return;
}
//

int main() {
    string main_file = "in.txt";
    fstream file(main_file);
    if (!file) {
        cerr << "Unable to read file";
        return 1;
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
    day6(grid, pos);
    day6Part2(grid, pos);

    return 0;
}
