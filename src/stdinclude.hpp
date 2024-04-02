#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <array>
#define ASSETS_FILE_PATH std::string("assets/")
#define KEYBOARD_STATE const uint8_t*
#define KEYBOARD_STATE_MUTABLE uint8_t*

enum Direction_Vector {
    Back = -1,
    Neutral = 0,
    Front = 1
};

struct Vector2 {
    float x;
    float y;
};

inline Vector2 operator+(Vector2& v1, Vector2& v2) {
    return {v1.x += v2.x, v1.y += v2.y};
}

inline Vector2 operator+=(Vector2& v1, Vector2 v2) {
    return {v1.x += v2.x, v1.y += v2.y};
}

class SpriteManager;

class Sprite {
    protected:
        friend class SpriteManager;
        std::string id;
    public:
        Sprite();
        Sprite(float x, float y, float z, float width, float height);
        virtual ~Sprite();
        void SetPostion(Vector2 position_v);
        void ChangePosition(Vector2 position_v);
        static void SpriteInputUpdate(Vector2 axis, SpriteManager &sprite_manager, double delta_time);
        Vector2 position;
        float z;
        float speed = 10.0f;
        SDL_Texture *texture = nullptr;
        SDL_Rect rect;
        SDL_Rect clip_rect;
        std::string GetId() { return id; }
};

class SpriteManager {
    static inline int16_t idCounter;
    static inline std::unordered_map<std::string, Sprite*> MasterManager;
    static inline std::vector<SpriteManager*> MasterManagerList;
    static inline std::vector<std::string> VoidList;
    public:
        ~SpriteManager();
        std::unordered_map<std::string, Sprite*> Map;
        void AddSprite(Sprite &sprite);
        void AddSprite(Sprite &sprite, std::string id);
        Sprite *GetSprite(std::string id);
        void RemoveSprite(std::string id);
        static std::string GenerateUniqueID();
        void EraseSprites();
        bool HasSprite(std::string id);
        bool DefinedId(std::string id);
};