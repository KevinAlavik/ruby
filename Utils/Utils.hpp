#pragma once

#include <string>

#define TO_VERSION(major, minor, patch) ((major << 16) | (minor << 8) | patch)

namespace Utils
{
    inline std::string VersionToString(int major, int minor, int patch)
    {
        return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
    }
}