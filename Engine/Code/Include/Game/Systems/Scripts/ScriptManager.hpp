
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <direct.h>


/*
class ScriptManager
{
public:
    bool CompileScriptToDLL(const std::string& scriptCppPath, const std::string& outputDllPath)
    {


        std::array<char, 1024> l_buffer{};
        if (_getcwd(l_buffer.data(), 1024) != nullptr)
            DEBUG_LOG_INFO("Current working directory: {}\n", l_buffer.data());

        std::string clangPath = "/Engine/Compiler/CLANG/bine/clang++.exe";
        std::string clangPath2 = "\"/Engine/Compiler/CLANG/bine/clang++.exe\"";

        if (!std::filesystem::exists(clangPath2))
        {
            DEBUG_LOG_ERROR("chemin non exist");
            //return false;
        }


        std::string command =
                clangPath2 + " -shared -std=c++20 " + scriptCppPath + " -o " + outputDllPath;

        std::cout << "[Compiling] " << command << std::endl;

        int result = system(command.c_str());
        return false;
    }
};*/
