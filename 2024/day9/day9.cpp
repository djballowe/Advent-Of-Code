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

struct FileNode {
    int id;
    int size;
    int space;
    FileNode *next;
    FileNode *prev;
};

FileNode buildDisk(vector<int> line) {
    int id = 0;
    FileNode start = {id, line[0], line[1]};
    FileNode *end = &start;

    for (int i = 2; i < line.size(); i += 2) {
        FileNode *next = new FileNode();
        next->id = ++id;
        next->size = line[i];
        if (i + 1 < line.size()) {
            next->space = line[i + 1];
        }
        next->prev = end;
        end->next = next;
        end = next;
    }

    FileNode *r = end;
    while (r) {
        FileNode *prev = r->prev;
        for (FileNode *l = &start; l != r && l; l = l->next) {
            if (l->space >= r->size) {
                if (r->prev) {
                    r->prev->next = r->next;
                    r->prev->space += r->space + r->size;
                }
                if (r->next) {
                    r->next->prev = r->prev;
                }
                if (l->next) {
                    l->next->prev = r;
                    r->next = l->next;
                }
                r->space = l->space - r->size;
                l->space = 0;
                l->next = r;
                r->prev = l;
                break;
            }
        }
        r = prev;
    }

    return start;
}

void day9Part2(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    long ans = 0;

    while (getline(file, line)) {
        vector<int> int_line = parseLine(line);
        FileNode disk = buildDisk(int_line);
        FileNode *ptr = &disk;
        int check = 0;
        while (ptr) {
            long product = 0;
            int count = ptr->size;
            while (count) {
                product += ptr->id * check;
                count--;
                check++;
            }

            int spaceCount = ptr->space;
            while (spaceCount) {
                spaceCount--;
                check++;
            }
            ans += product;
            ptr = ptr->next;
        }
    }

    file.close();
    return;
}
//

int main() {
    string main_file = "in.txt";
    string test_file = "in-test.txt";
    day9(main_file);
    day9Part2(main_file);

    return 0;
}
