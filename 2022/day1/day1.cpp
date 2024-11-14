#include "iostream"
#include <fstream>
#include <string>

int main() {
    std::fstream file("day1-test.txt");
    if (!file) {
        std::cerr << "Unable to read file";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
    return 0;
}
