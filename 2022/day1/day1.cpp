#include "iostream"
#include <algorithm>
#include <fstream>
#include <string>

int main() {
    std::fstream file("day1.txt");
    if (!file) {
        std::cerr << "Unable to read file";
        return 1;
    }

    std::string line;
    int count = 0;
    int largest = 0;
    while (std::getline(file, line)) {
        if (line == "") {
            largest = std::max(largest, count);
            count = 0;
        } else {
            count += std::stoi(line);
        }
    }

    std::cout << largest << std::endl;

    file.close();
    return 0;
}
