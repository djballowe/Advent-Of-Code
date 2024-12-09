#include "iostream"
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> parseDisk(vector<int> line) {
    vector<int> disk;
    int l = 0;
    int r = line.size() - 1;
    int idl = 0;
    int idr = (line.size() - 1) / 2;

    int space = line[1];
    int memory = line[r];

    while (l < r) {
        if (l % 2 == 0) {
            int count = line[l];
            while (count) {
                disk.push_back(idl);
                count--;
            }
            idl++;
            l++;
        } else {
            while (space && memory) {
                space--;
                memory--;
                disk.push_back(idr);
            }
            if (!memory) {
                idr--;
                r -= 2;
                memory = line[r];
            }

            if (!space) {
                l++;
                space = line[l + 1];
            }
        }
    }

    while (space) {
        space--;
        disk.push_back(idr);
    }

    return disk;
}

vector<int> parseLine(string line) {
    vector<int> nums;
    for (char num : line) {
        nums.push_back(num - '0');
    }

    return nums;
}

void day9(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    long ans = 0;
    while (getline(file, line)) {
        vector<int> int_line = parseLine(line);
        vector<int> disk = parseDisk(int_line);
        for (int val : disk) {
            cout << val;
        }
        cout << endl;
        for (int i = 0; i < disk.size(); i++) {
            ans += disk[i] * i;
        }
    }

    cout << ans << endl;

    file.close();
    return;
}
//

// Part 2
void day9Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;

    while (getline(file, line)) {
        vector<int> int_line = parseLine(line);
    }

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    // day9(main_file);
    day9Part2(test_file);

    return 0;
}
