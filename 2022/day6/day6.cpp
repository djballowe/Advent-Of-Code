#include "iostream"
#include <fstream>
#include <map>
#include <string>

using namespace std;

void day6Part1(string path) {
    map<char, int> char_count;
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    getline(file, line);
    int l = 0;
    int r = 3;
    string freq = "";
    int ans = 0;

    while (r < line.size()) {
        for (int i = l; l <= r; i++) {
            char key = line[i];
            if (char_count[key] || freq.size() == 14) {
                if (freq.size() == 14) {
                    ans = i;
                    break;
                }
                char_count.clear();
                freq = "";
                l++;
                r++;
                break;
            }
            char_count[key]++;
            freq += key;
        }
        if (ans) {
            break;
        }
    }

    cout << ans << endl;
    file.close();
    return;
}

int main() {
    string mainFile = "day6.txt";
    string testFile = "day6-test.txt";
    day6Part1(mainFile);

    return 0;
}
