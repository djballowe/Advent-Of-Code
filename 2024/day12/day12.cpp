#include "iostream"
#include "vector"
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void parseLine(string line, int &j, map<char, vector<pair<int, int>>> &plants) {
    for (int i = 0; i < line.size(); i++) {
        plants[line[i]].push_back({i, j});
    }
    return;
}

bool inBounds(int x, int y, vector<string> &grid) {
    int cols = grid.size();
    int rows = grid[0].size();

    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        return true;
    }

    return false;
}

// dfs flood
void flood(char plant, int x, int y, vector<string> &grid, map<int, vector<pair<int, int>>> &plots, int &plot) {
    char curr_plant = grid[y][x];
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    grid[y][x] = '+';
    plots[plot].push_back({x, y});

    for (pair<int, int> direction : directions) {
        if (inBounds(x + direction.first, y + direction.second, grid)) {
            char new_plant = grid[y + direction.second][x + direction.first];
            if (new_plant == plant) {
                flood(plant, x + direction.first, y + direction.second, grid, plots, plot);
            }
        }
    }
    return;
}

void findPerimeter(pair<int, int> cords, int &perim, vector<string> &grid) {
    int x = cords.first;
    int y = cords.second;
    char plant = grid[y][x];
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (pair<int, int> direction : directions) {
        if (inBounds(x + direction.first, y + direction.second, grid)) {
            char new_plant = grid[y + direction.second][x + direction.first];
            if (new_plant != plant) {
                perim++;
            }
        } else {
            perim++;
        }
    }
    return;
}

void day12(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    vector<string> grid;
    int j = 0;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
        j++;
    }

    vector<string> visited = grid;
    map<int, vector<pair<int, int>>> plots;
    int plot = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (visited[i][j] != '+') {
                plot++;
                flood(visited[i][j], j, i, visited, plots, plot);
            }
        }
    }

    int perim = 0;
    int ans = 0;
    for (const auto &[key, val] : plots) {
        int area = val.size();
        for (pair<int, int> cords : val) {
            findPerimeter(cords, perim, grid);
        }
        ans += area * perim;
        perim = 0;
    }

    cout << "part 1: " << ans << endl;

    file.close();
    return;
}

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    day12(main_file);
    return 0;
}
