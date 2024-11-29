#include "iostream"
#include <algorithm>
#include <deque>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void fillBoxLayout(vector<vector<char>> &boxes, string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int count = 0;
    int rowCount = 0;
    getline(file, line);
    for (int i = 0; i < line.size(); i++) {
        count++;
        if (count % 3 == 0) {
            i++;
            rowCount++;
        }
    }

    while (rowCount) {
        boxes.push_back({});
        rowCount--;
    }

    file.close();
    return;
}

void storeBoxes(vector<vector<char>> &boxes, string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    int row = 0;
    int count = 0;
    while (getline(file, line)) {
        for (int i = 0; i < line.size(); i++) {
            count++;
            if (line[i] >= 65 && line[i] <= 90) {
                boxes[row].push_back(line[i]);
            }
            if (count % 3 == 0) {
                i++;
                row++;
            }
        }
        row = 0;
    }

    for (vector<char> &row : boxes) {
        reverse(row.begin(), row.end());
    }

    file.close();
    return;
}

void moveBoxes(vector<vector<char>> &boxes, string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<int> instructions;
        string instruction = "";
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= 48 && line[i] <= 57) {
                instruction += line[i];
                if (instruction != "" &&
                    (i == line.size() - 1 || line[i + 1] == ' ')) {
                    instructions.push_back(stoi(instruction));
                    instruction = "";
                }
            }
        }

        int target = instructions[1] - 1;
        int destination = instructions[2] - 1;
        int count = instructions[0];
        deque<char> crane;
        while (count) {
            int top = boxes[target].back();
            crane.push_front(top);
            boxes[target].pop_back();
            count--;
        }

        for (char val : crane) {
            boxes[destination].push_back(val);
        }
        crane.clear();
    }
    file.close();
    return;
}

int main() {
    string mainFile = "day5.txt";
    string boxFile = "day5-boxes.txt";
    vector<vector<char>> boxes;
    fillBoxLayout(boxes, boxFile);
    storeBoxes(boxes, boxFile);
    moveBoxes(boxes, mainFile);
    for (vector<char> &box : boxes) {
        cout << box.back();
    }
    cout << endl;

    return 0;
}
