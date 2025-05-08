#pragma once

#include <raylib-cpp.hpp>

namespace Render
{
    class Texture
    {
    public:
        explicit Texture(const raylib::Image &image);
        ~Texture();

        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;

        Texture(Texture &&other) noexcept;
        Texture &operator=(Texture &&other) noexcept;

        const raylib::Texture2D &GetTexture() const;
        int GetWidth() const;
        int GetHeight() const;
        bool IsValid() const;

    private:
        raylib::Texture2D texture_;
    };
}
