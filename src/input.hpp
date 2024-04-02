#pragma once
#include "enginedata.hpp"

namespace Input {
    extern SpriteManager Controlled_Sprites;
    extern KEYBOARD_STATE state;
    extern std::array<uint8_t, SDL_NUM_SCANCODES> p_state;
    void ReadInput(EngineWindow &window);
}