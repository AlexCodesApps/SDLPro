#include "../stdinclude.hpp"

Sprite::Sprite() : z(0) {
    position = {0, 0};
    texture = nullptr;
    rect = {0, 0, 100, 100};
    clip_rect = {0, 0, 0, 0};
}

Sprite::Sprite(float x, float y, float z, float width, float height) : z(z) {
    position = {x, y};
    rect = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
    clip_rect = {0, 0, 0, 0};
}

Sprite::~Sprite() {
    if (texture != nullptr) SDL_DestroyTexture(texture);
}

void Sprite::SetPostion(Vector2 position) {
    this->position = position;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
}

void Sprite::ChangePosition(Vector2 position_v) {
    SetPostion({position.x + position_v.x, position.y + position_v.y});
}

void (Sprite::SpriteInputUpdate)(Vector2 axis, SpriteManager &sprite_manager, double delta_time) {
    if (axis.x == 0.0f && axis.y == 0.0f) return;
    float rad_angle = SDL_atan2f(axis.y, axis.x);
    for (auto &pl: sprite_manager.Map) {
        pl.second->ChangePosition({SDL_cosf(rad_angle) * static_cast<float>(delta_time) * pl.second->speed, SDL_sinf(rad_angle) * static_cast<float>(delta_time) * pl.second->speed});
    }
}

SpriteManager::~SpriteManager() {
    EraseSprites();
}

std::string SpriteManager::GenerateUniqueID() {
    std::string n_id = "Sprite." + std::to_string(idCounter++);
    while (std::find(VoidList.begin(), VoidList.end(), n_id) != VoidList.end()) {
        n_id = "Sprite." + std::to_string(idCounter++);
    }
    std::cout << "ID: " << n_id << std::endl;
    return n_id;
}

bool SpriteManager::HasSprite(std::string id) {
    return Map.find(id) != Map.end();
}

bool SpriteManager::DefinedId(std::string id) {
    return MasterManager.find(id) != MasterManager.end();
}

void SpriteManager::AddSprite(Sprite &sprite) {
    if (HasSprite(sprite.id)) return;
    if (!DefinedId(sprite.id)) {
        sprite.id = SpriteManager::GenerateUniqueID();
        MasterManager.insert({sprite.id, &sprite});
    }
    Map.insert({sprite.id, &sprite});
}

void SpriteManager::AddSprite(Sprite &sprite, std::string id) {
    if (HasSprite(sprite.id)) {
        std::cout<<"Sprite id already exists in Map!\n";
        return;
    }
    if (!DefinedId(id)) {
        for (auto s : VoidList) {
            if (s == id) return;
        }
        VoidList.push_back(id);
        sprite.id = id;
        MasterManager.insert({id, &sprite});
    }
    else {
        std::cout<<"Sprite id already exists!\n";
    }
    Map.insert({id, &sprite});
}

Sprite *SpriteManager::GetSprite(std::string id) {
    if (!HasSprite(id)) return nullptr;
    return Map[id];
}

void SpriteManager::RemoveSprite(std::string id) {
    if (!HasSprite(id)) return;
    Map.erase(id);
    MasterManager.erase(id);
    VoidList.erase(std::remove(VoidList.begin(), VoidList.end(), id), VoidList.end());
    std::cout << "Sprite " << id << " removed." << std::endl;
}

void SpriteManager::EraseSprites() {
    while(Map.size() > 0) RemoveSprite(Map.begin()->first);
}