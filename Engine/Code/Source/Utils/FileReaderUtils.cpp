#include "Utils/FileReaderUtils.hpp"

#include "Logger.hpp"

std::vector<char> FileReaderUtils::ReadFile(const std::string& a_filename)
{
    std::ifstream l_file(a_filename, std::ios::binary | std::ios::ate);

    if (!l_file.is_open())
        throw std::runtime_error("Failed to open file " + a_filename);

    const size_t fileSize = static_cast<size_t>(l_file.tellg());
    std::vector<char> l_fileBuffer(fileSize);

    l_file.seekg(0);
    l_file.read(l_fileBuffer.data(), fileSize);
    l_file.close();

    DEBUG_LOG_VERBOSE("File {} opened successfully!", a_filename);

    return l_fileBuffer;
}
