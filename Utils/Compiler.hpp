#pragma once

#include <string>

class Compiler
{
public:
        static std::string getCompilerVersion()
        {
#if defined(__clang__)
                return "Clang v" + std::to_string(__clang_major__) + "." + std::to_string(__clang_minor__);
#elif defined(__GNUC__)
                return "GCC v" + std::to_string(__GNUC__) + "." + std::to_string(__GNUC_MINOR__) + "." + std::to_string(__GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
                return "MSVC v" + std::to_string(_MSC_VER);
#else
                return "Unknown Compiler";
#endif
        }
};
