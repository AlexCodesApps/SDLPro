#pragma once
#include "stdinclude.hpp"

class EngineWindow {
    public:
        std::string title = "Undefined";
        static constexpr int SCREEN_WIDTH = 600;
        static constexpr int SCREEN_HEIGHT = 400;
        static inline bool running = true;
        static inline uint64_t CurrentMilli = 0.0f;
        static inline double CurrentTime = 0.0f;
        static inline double DeltaTime = 0.0f;
        double scale = 4.0f;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        std::vector<Sprite*> RenderList;
        static inline SDL_Event event;
        ~EngineWindow();
};

SDL_Texture *LoadTexture(EngineWindow &window, std::string path);

SDL_Texture *LoadTexture(EngineWindow &window, std::string path, SDL_Rect &clip);

SDL_Rect ScaleRect(SDL_Rect &rect, float scale);

SDL_Rect ScaleRect(Sprite &sprite, float scale);

void Draw_Screen(EngineWindow &window);

void Draw_Sprite(Sprite &sprite, EngineWindow &window);