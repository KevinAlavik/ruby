#include <raylib-cpp.hpp>
#include <spdlog/spdlog.h>
#include <config.hpp>

#include <Utils/Compiler.hpp>
#include <Utils/Utils.hpp>
#include <Render/Texture.hpp>
#include <Render/TextureManager.hpp>

namespace Core
{
    class Game
    {
    public:
        Game()
        {
#ifndef NDEBUG
            spdlog::set_level(spdlog::level::trace);
#else
            spdlog::set_level(spdlog::level::info);
#endif
            spdlog::info("Ruby v{} built with {}, raylib v{}, spdlog v{}",
                         GAME_VERSION,
                         Compiler::getCompilerVersion(), RAYLIB_VERSION,
                         Utils::VersionToString(SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH));
#ifndef NDEBUG
            SetTraceLogLevel(LOG_WARNING);
#endif
            window = raylib::Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Ruby");
            window.SetTargetFPS(TARGET_FPS);
            if (!LoadResources())
                throw std::runtime_error("Resource loading failed");
        }

        ~Game()
        {
            UnloadResources();
            spdlog::info("Game resources cleaned up.");
        }

        void Run()
        {
            while (!window.ShouldClose())
            {
                Update();
                Render();
            }
        }

    private:
        raylib::Window window;
        Render::TextureManager textureManager;

        /* Internal Textures */
        const Render::Texture *tex_raylibLogo = nullptr;

        bool LoadResources()
        {
            try
            {
                tex_raylibLogo = &textureManager.LoadTexture(TEXTURE_RAYLIB_LOGO_PATH);
            }
            catch (const std::exception &e)
            {
                spdlog::error("Failed to load Raylib logo texture: {}", e.what());
                return false;
            }
            return true;
        }

        void UnloadResources()
        {
            textureManager.UnloadAllTextures();
        }

        void Update()
        {
            /* no input handling yet */
        }

        void Render()
        {
            window.BeginDrawing();
            window.ClearBackground(RAYWHITE);
            if (tex_raylibLogo && tex_raylibLogo->IsValid())
            {
                // Draw the texture at the center of the screen
                tex_raylibLogo->GetTexture().Draw(
                    (SCREEN_WIDTH - tex_raylibLogo->GetWidth()) / 2,
                    (SCREEN_HEIGHT - tex_raylibLogo->GetHeight()) / 2);
            }
            window.EndDrawing();
        }
    };
}

int main()
{
    try
    {
        Core::Game game;
        game.Run();
    }
    catch (const std::exception &e)
    {
        spdlog::critical("Fatal error: {}", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
