#include "iostream"
#include <fstream>
#include <string>

using namespace std;

void day7(string path) {
    fstream file(path);
    if (!file) {
        cerr << "Unable to read file";
        return;
    }

    string line;
    while (getline(file, line)) {
    }

    file.close();
    return;
}

int main() {
    string mainFile = "day7.txt";
    string testFile = "day7-test.txt";
    day7(testFile);

    return 0;
}
