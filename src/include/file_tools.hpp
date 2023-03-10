#pragma once

#include <fstream>
#include <streambuf>
#include <sstream>

std::string get_file_contents(char *filepath) {
    std::ifstream t(filepath);
    std::stringstream strStream;

    strStream << t.rdbuf();
    return strStream.str();

    }
