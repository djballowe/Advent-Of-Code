#include "helpers.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

std::vector<std::string> AdventHelpers::parseLines(std::string path) {
    std::vector<std::string> input_vector;
    std::fstream file(path);
    if (!file) {
        std::cerr << "Unable to read file";
        throw std::runtime_error("Error: unable to open file at path " + path);
    }

    std::string line;
    while (std::getline(file, line)) {
        input_vector.push_back(line);
    }

    return input_vector;
}
