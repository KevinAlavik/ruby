#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <Render/Texture.hpp>

namespace Render
{
    class TextureManager
    {
    public:
        TextureManager() = default;
        ~TextureManager();

        TextureManager(const TextureManager &) = delete;
        TextureManager &operator=(const TextureManager &) = delete;

        const Texture &LoadTexture(const std::string &filePath);
        const Texture &GetTexture(const std::string &filePath) const;

        void UnloadAllTextures();

    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
    };
}
