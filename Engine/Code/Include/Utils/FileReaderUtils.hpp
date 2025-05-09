#pragma once

#include <string>
#include <vector>

class FileReaderUtils
{
public:
    static std::vector<char> ReadFile(const std::string& a_filename);
};