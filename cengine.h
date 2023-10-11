#ifndef Cengine_H
#define Cengine_H

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
// imgui
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"


class Cengine
{
public:
        Cengine();
        ~Cengine();
        bool isRunning;
        bool usingGUI;
        void Init(int width, int height, const char* title, bool useGUI);
        void HandleInput();
        void Update();
        void Draw();
        void Clean();
        void CreateImgui();
        void UpdateGui();
        SDL_GLContext ctx;
        SDL_Renderer* ren;
        SDL_Window* win;
        ImGuiIO io;
        ImVec4 clear_color;
};


#endif
