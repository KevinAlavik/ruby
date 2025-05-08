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
            spdlog::trace("TextureManager::LoadTexture - returning cached texture: {}", filePath);
            return *it->second;
        }

        spdlog::trace("TextureManager::LoadTexture - loading texture from: {}", filePath);
        raylib::Image img(filePath);
        if (!img.IsValid())
        {
            spdlog::error("TextureManager::LoadTexture - failed to load image: {}", filePath);
            throw std::runtime_error("Failed to load image: " + filePath);
        }

        auto texture = std::make_unique<Texture>(img);

        spdlog::trace("TextureManager::LoadTexture - created Texture object for: {} (id={}, {}x{})",
                      filePath, texture->GetTexture().id, texture->GetWidth(), texture->GetHeight());

        const Texture &ref = *texture;
        textures_.emplace(filePath, std::move(texture));
        return ref;
    }

    const Texture &TextureManager::GetTexture(const std::string &filePath) const
    {
        auto it = textures_.find(filePath);
        if (it == textures_.end())
        {
            spdlog::error("TextureManager::GetTexture - texture not found: {}", filePath);
            throw std::runtime_error("Texture not found: " + filePath);
        }
        return *it->second;
    }

    void TextureManager::UnloadAllTextures()
    {
        for (auto &pair : textures_)
        {
            pair.second.reset();
        }
        textures_.clear();
        spdlog::info("TextureManager::UnloadAllTextures - all textures unloaded.");
    }
}
