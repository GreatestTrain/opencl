#pragma once

#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>

template <typename T>
void get_matrix(char* filepath, std::vector<T> data) {
    std::ifstream t(filepath);
    std::string line;

    if (t.is_open() && t.good()) {
      while (std::getline(t, line)) {
        data.push_back(std::stof(line));
        }
    }

}

inline std::string get_file_contents(char *filepath) {
    std::ifstream t(filepath);
    std::stringstream strStream;

    strStream << t.rdbuf();
    return strStream.str();

    }
