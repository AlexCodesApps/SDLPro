#include "enginedata.hpp"
#include "input.hpp"
#include "physics_sprite.hpp"

Sprite *player;
Sprite *enemy;
MovingSprite *ball;

void UpdatePong(EngineWindow &window) {
    player->position.x = 0.0f;
    if (player->position.y < 0.0f) player->position.y = 0.0f;
    if (player->position.y > EngineWindow::SCREEN_HEIGHT - player->rect.h) player->position.y = EngineWindow::SCREEN_HEIGHT - player->rect.h;
    if (ball->position.y < 0.0f || ball->position.y > EngineWindow::SCREEN_HEIGHT - ball->rect.h) {
        ball->velocity.y *= -1.0f;
    }
    static Sprite *temparr[2] = {enemy, player};
    for (int i = 0; i < 2; i++) {
        if (SDL_HasIntersection(&ball->rect, &temparr[i]->rect)) {
            ball->velocity.x = SDL_fabsf(ball->velocity.x) * ((i*2)-1);
            std::cout<<"Ball hit! "<< (i*2)-1 << std::endl;
            ball->velocity = {ball->velocity.x * 1.01f, ball->velocity.y * 1.1f};
            break;
        }
    }
    if (ball->position.x < 0.0f || ball->position.x > EngineWindow::SCREEN_WIDTH - ball->rect.w) {
        std::cout<<"Ball out of bounds!"<<std::endl;
        EngineWindow::running = false;
    }
    if (enemy->rect.y + static_cast<int>(static_cast<float>(enemy->rect.h)/2) - static_cast<int>(static_cast<float>(ball->rect.h)/2) > ball->rect.y) {
        enemy->ChangePosition({0.0f, -enemy->speed * static_cast<float>(EngineWindow::DeltaTime)});
    }
    if (enemy->rect.y < ball->rect.y) {
        enemy->ChangePosition({0.0f, enemy->speed * static_cast<float>(EngineWindow::DeltaTime)});
    }
    if (enemy->rect.y + static_cast<int>(static_cast<float>(enemy->rect.h)/2) > EngineWindow::SCREEN_HEIGHT) {
        enemy->SetPostion({static_cast<float>(enemy->rect.x), 0.0f});
    }
    else if (enemy->rect.y < 0) {
        enemy->SetPostion({static_cast<float>(enemy->rect.x), EngineWindow::SCREEN_HEIGHT});
    }
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Input::state = SDL_GetKeyboardState(nullptr);
    EngineWindow SDLPro;
    SDLPro.title = "SDL2 Window";
    SDLPro.scale = 1000.0f;
    ball = new MovingSprite(0.0f, 100.0f, 0.0f, 50.0f, 50.0f, {120.0f, 60.0f});
    player = new Sprite(0.0f, EngineWindow::SCREEN_HEIGHT / 2 - 50.0f, 0.0f, 25.0f, 100.0f);
    enemy = new Sprite(EngineWindow::SCREEN_WIDTH - 25.0f, EngineWindow::SCREEN_HEIGHT / 2 - 50.0f, 0.0f, 25.0f, 100.0f);
    ball->speed = 200.0f;
    SDLPro.RenderList.push_back(ball);
    SDLPro.RenderList.push_back(player);
    SDLPro.RenderList.push_back(enemy);
    player->speed = 100.0f;
    enemy->speed = 75.0f;
    Input::Controlled_Sprites.AddSprite(*player);
    SDLPro.window = SDL_CreateWindow(SDLPro.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDLPro.SCREEN_WIDTH, SDLPro.SCREEN_HEIGHT, SDL_WINDOW_METAL);
    SDLPro.renderer = SDL_CreateRenderer(SDLPro.window, -1, 0);
    SDL_RenderSetVSync(SDLPro.renderer, 1);
    ball->texture = LoadTexture(SDLPro, "whitecircle.png", ball->clip_rect);
    player->texture = LoadTexture(SDLPro, "rect.png", player->clip_rect);
    enemy->texture = LoadTexture(SDLPro, "rect.png", enemy->clip_rect);
    if (SDLPro.window == nullptr || SDLPro.renderer == nullptr) {
        std::cout << "Error creating window or renderer\n";
        SDL_GetError();
        exit(EXIT_FAILURE);
    }
    while (EngineWindow::running) {
        EngineWindow::DeltaTime = (static_cast<double>(SDL_GetTicks64()) - EngineWindow::CurrentMilli)/1000.0;
        EngineWindow::CurrentMilli = static_cast<double>(SDL_GetTicks64());
        UpdatePong(SDLPro);
        Input::ReadInput(SDLPro);
        Draw_Screen(SDLPro);
        MovingSprite::PhysicsSpriteUpdate();
    }
    free (player);
    SDL_Quit();
    return 0;
}