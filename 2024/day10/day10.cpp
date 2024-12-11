#include "iostream"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void buildGrid(string line, vector<vector<int>> &grid, vector<pair<int, int>> &starts, int &j) {
    vector<int> int_line;
    for (int i = 0; i < line.size(); i++) {
        int val = line[i] - '0';
        int_line.push_back(val);
        if (val == 0) {
            pair<int, int> cords = {i, j};
            starts.push_back(cords);
        }
    }
    grid.push_back(int_line);
}

bool inBounds(vector<vector<int>> &grid, pair<int, int> cord) {
    int cols = grid.size();
    int rows = grid[0].size();

    if (cord.first >= 0 && cord.first < rows && cord.second >= 0 && cord.second < cols) {
        return true;
    }
    return false;
}

void getTrailScore(pair<int, int> curr, int &score, vector<vector<int>> &grid) {
    vector<pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int num = grid[curr.second][curr.first];
    if (num == 9) {
        score++;
        return;
    }

    for (int i = 0; i < directions.size(); i++) {
        pair<int, int> adjacent = {curr.first + directions[i].first, curr.second + directions[i].second};
        if (inBounds(grid, adjacent)) {
            int next_node = grid[adjacent.second][adjacent.first];
            if (next_node == num + 1) {
                getTrailScore(adjacent, score, grid);
            }
        }
    }
}

void day10(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    vector<vector<int>> grid;
    vector<pair<int, int>> starts;
    int j = 0;
    while (getline(file, line)) {
        buildGrid(line, grid, starts, j);
        j++;
    }

    int ans = 0;
    int score = 0;
    for (int i = 0; i < starts.size(); i++) {
        pair<int, int> start = starts[i];
        getTrailScore(start, score, grid);
        ans += score;
        score = 0;
    }

    cout << "ans: " << ans << endl;

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    day10(main_file);
    return 0;
}
