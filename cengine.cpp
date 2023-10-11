#include <SDL2/SDL_video.h>
#include <iostream>
#include "cengine.h"
#include "imgui_impl_sdlrenderer2.h"

Cengine::Cengine()
{
    // Initialize io in the constructor
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO();
}
Cengine::~Cengine()
{}

// This method creates a new SDL window and context
void Cengine::Init(int width, int height, const char* title, bool useGUI)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl; return;
    }

    // Create window and choose graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    // Error check window
    if (!win)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; return;
    }
    ren = SDL_CreateRenderer(win,-1, 0);
    if (!ren)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl; return;
    }

    isRunning = true;
}

void Cengine::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(win))
            isRunning = false;
    }
}

void Cengine::Update() {}

void Cengine::CreateImgui()
{
    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForSDLRenderer(win, ren);
    ImGui_ImplSDLRenderer2_Init(ren);
}

void Cengine::UpdateGui()
{
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // Create a simple window with a button
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    ImGui::End();




    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(ren, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(ren, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(ren);

    // Draw a square in the middle of the screen with SDL2
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect rect = { 250, 250, 100, 100 };
    SDL_RenderFillRect(ren, &rect);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());


    SDL_RenderPresent(ren);
}

void Cengine::Draw()
{

}


void Cengine::Clean()
{
    // Cleanup imgui
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    // Cleanup SDL
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
