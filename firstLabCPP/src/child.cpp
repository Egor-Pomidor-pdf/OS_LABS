#include <iostream>
#include <fstream>
#include <string>
#include "../include/utils.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "No filename provided" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(std::cin, line)) {
        std::string reversed = reverseString(line);
        file << reversed << std::endl;
        std::cout << reversed << std::endl;  // Вывод в stdout
    }

    file.close();
    return 0;
}