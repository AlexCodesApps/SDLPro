#include "../physics_sprite.hpp"

MovingSprite::MovingSprite(float x, float y, float z, float width, float height, Vector2 velocity_p)  : Sprite(x, y, z, width, height) {
    MovingSprite::PhysicsSpriteManager.AddSprite(*this);
    velocity = velocity_p;
}

MovingSprite::~MovingSprite() {
    MovingSprite::PhysicsSpriteManager.RemoveSprite(GetId());
}

void MovingSprite::PhysicsSpriteUpdate() {
    for (auto &pl: MovingSprite::PhysicsSpriteManager.Map) {
        pl.second->ChangePosition({static_cast<MovingSprite*>(pl.second)->velocity.x * static_cast<float>(EngineWindow::DeltaTime),
        static_cast<MovingSprite*>(pl.second)->velocity.y * static_cast<float>(EngineWindow::DeltaTime)});
    }
}

void MovingSprite::ReverseVelocity() {
    velocity = {velocity.x * -1.0f, velocity.y * -1.0f};
}

