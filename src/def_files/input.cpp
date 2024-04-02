#include "../input.hpp"

SpriteManager Input::Controlled_Sprites;
KEYBOARD_STATE Input::state = nullptr;
std::array<uint8_t, SDL_NUM_SCANCODES> Input::p_state = {0};

void Input::ReadInput(EngineWindow &window) {
    std::copy(Input::state, &Input::state[SDL_NUM_SCANCODES], Input::p_state.begin());
    while (SDL_PollEvent(&EngineWindow::event)) {
        if (EngineWindow::event.type == SDL_QUIT) EngineWindow::running = false;
    }
    Vector2 axis = {0.0f, 0.0f};
    if (Input::state[SDL_SCANCODE_UP]) axis.y = -1.0f;
    if (Input::state[SDL_SCANCODE_DOWN]) axis.y = 1.0f;
    if (Input::state[SDL_SCANCODE_LEFT]) axis.x = -1.0f;
    if (Input::state[SDL_SCANCODE_RIGHT]) axis.x = 1.0f;
    Sprite::SpriteInputUpdate(axis, Input::Controlled_Sprites, EngineWindow::DeltaTime);
}