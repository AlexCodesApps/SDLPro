#include "../enginedata.hpp"

EngineWindow::~EngineWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Texture *LoadTexture(EngineWindow &window, std::string path) {
    std::string full_path = ASSETS_FILE_PATH + path;
    SDL_Surface *surface = IMG_Load(full_path.c_str());
    if (surface == nullptr) {
        std::cout << "Error loading image" << std::endl;
        SDL_GetError();
        exit(EXIT_FAILURE);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window.renderer, surface);
    if (texture == nullptr) {
        std::cout << "Error loading texture" << std::endl;
        SDL_GetError();
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture *LoadTexture(EngineWindow &window, std::string path, SDL_Rect &clip) {
    std::string full_path = ASSETS_FILE_PATH + path;
    SDL_Surface *surface = IMG_Load(full_path.c_str());
    if (surface == nullptr) {
        std::cout << "Error loading image" << std::endl;
        std::cout << SDL_GetError();
        exit(EXIT_FAILURE);
    }
    if (window.renderer == nullptr) {
    std::cerr << "Error Renderer is null: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
}
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window.renderer, surface);
    if (texture == nullptr) {
        std::cout << "Error loading texture" << std::endl;
        std::cout << SDL_GetError();
        exit(EXIT_FAILURE);
    }
    clip.w = surface->w;
    clip.h = surface->h;
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Rect ScaleRect(SDL_Rect &rect, float scale) {
    SDL_Rect n_rect = {static_cast<int>(rect.x * scale), static_cast<int>(rect.y * scale), static_cast<int>(rect.w * scale), static_cast<int>(rect.h * scale)};
    return n_rect;
}

SDL_Rect ScaleRect(Sprite &sprite, float scale) {
    SDL_Rect n_rect = {static_cast<int>(sprite.position.x * scale), static_cast<int>(sprite.position.y * scale), static_cast<int>(sprite.rect.w * scale), static_cast<int>(sprite.rect.h * scale)};
    return n_rect;
}

void Draw_Screen(EngineWindow &window) {
    std::sort(window.RenderList.begin(), window.RenderList.end(), [] (Sprite* a, Sprite* b) { return a->z < b->z; });
    for (auto s : window.RenderList) {
        Draw_Sprite(*s, window);
    }
    SDL_RenderPresent(window.renderer);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 0);
    SDL_RenderClear(window.renderer);
}

void Draw_Sprite(Sprite &sprite, EngineWindow &window) {
    SDL_RenderCopy(window.renderer, sprite.texture, &sprite.clip_rect, &sprite.rect);
}