#include <Render/Texture.hpp>
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace Render
{
    Texture::Texture(const raylib::Image &image)
        : texture_(image)
    {
        if (texture_.id == 0)
        {
            spdlog::error("Texture::Texture - failed to create Texture2D from image");
            throw std::runtime_error("Failed to create Texture2D from image");
        }
        spdlog::trace("Texture::Texture - created Texture2D (id={}, {}x{})", texture_.id, texture_.width, texture_.height);
    }

    Texture::~Texture()
    {
        if (texture_.id != 0)
        {
            texture_.Unload();
            spdlog::trace("Texture::Texture - Texture2D unloaded (id={})", texture_.id);
        }
    }

    const raylib::Texture2D &Texture::GetTexture() const
    {
        return texture_;
    }

    int Texture::GetWidth() const
    {
        return texture_.width;
    }

    int Texture::GetHeight() const
    {
        return texture_.height;
    }

    bool Texture::IsValid() const
    {
        return texture_.id != 0;
    }
}
