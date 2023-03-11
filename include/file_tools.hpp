#pragma once

#include <cstdlib>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
void get_matrix(char* filepath, std::vector<T>& data) {
    std::ifstream t(filepath);
    std::string line;

    if (t.is_open() && t.good()) {

        typename std::vector<T>::iterator it = data.begin();

        while (std::getline(t, line)) {
            (*it) = std::stof(line);
            it++;
        }
    }

}

inline std::string get_file_contents(char *filepath) {
    std::ifstream t(filepath);
    std::stringstream strStream;

    strStream << t.rdbuf();
    return strStream.str();

    }
