#include <Render/TextureManager.hpp>
#include <spdlog/spdlog.h>
#include <stdexcept>

namespace Render
{
    TextureManager::~TextureManager()
    {
        UnloadAllTextures();
    }

    const Texture &TextureManager::LoadTexture(const std::string &filePath)
    {
        auto it = textures_.find(filePath);
        if (it != textures_.end())
        {
            spdlog::trace("TextureManager::LoadTexture - Reusing cached texture: {}", filePath);
            return *it->second;
        }

        spdlog::trace("TextureManager::LoadTexture - Loading image from: {}", filePath);
        raylib::Image image(filePath);

        if (!image.IsValid())
        {
            spdlog::error("TextureManager::LoadTexture - Invalid image: {}", filePath);
            throw std::runtime_error("Failed to load image: " + filePath);
        }

        auto texture = std::make_unique<Texture>(image);
        const Texture &ref = *texture;

        textures_.emplace(filePath, std::move(texture));
        spdlog::trace("TextureManager::LoadTexture - Texture loaded and stored: {}", filePath);

        return ref;
    }

    const Texture &TextureManager::GetTexture(const std::string &filePath) const
    {
        auto it = textures_.find(filePath);
        if (it == textures_.end())
        {
            spdlog::error("TextureManager::GetTexture - Texture not found: {}", filePath);
            throw std::runtime_error("Texture not found: " + filePath);
        }

        return *it->second;
    }

    void TextureManager::UnloadAllTextures()
    {
        textures_.clear();
        spdlog::info("TextureManager::UnloadAllTextures - All textures unloaded.");
    }
}
