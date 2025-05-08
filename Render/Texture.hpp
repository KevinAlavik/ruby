#pragma once

#include <raylib-cpp.hpp>
#include <string>

namespace Render
{
    class Texture
    {
    public:
        explicit Texture(raylib::Image image);
        ~Texture();

        const raylib::Texture2D &GetTexture() const;

        int GetWidth() const;
        int GetHeight() const;

        bool IsValid() const;

    private:
        raylib::Texture2D texture_;
    };
}
