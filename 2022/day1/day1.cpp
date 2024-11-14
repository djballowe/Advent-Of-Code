#include "iostream"
#include <fstream>
#include <string>

using namespace std;

int main() {
    fstream file("day1.txt");
    if (!file) {
        cerr << "Unable to read file";
        return 1;
    }

    string line;
    int count = 0;
    int top[3] = {0, 0, 0};
    while (getline(file, line)) {
        if (line == "") {
            if (count > top[0]) {
                top[2] = top[1];
                top[1] = top[0];
                top[0] = count;
            } else if (count > top[1]) {
                top[2] = top[1];
                top[1] = count;
            } else if (count > top[2]) {
                top[2] = count;
            }
            count = 0;
        } else {
            count += stoi(line);
        }
    }
    int ans = 0;
    for (int val : top) {
        ans += val;
        cout << val << endl;
    }
    cout << ans << endl;

    file.close();
    return 0;
}
