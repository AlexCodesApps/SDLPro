#pragma once
#include "stdinclude.hpp"
#include "enginedata.hpp"

class MovingSprite : public Sprite {
    protected:
        static inline SpriteManager PhysicsSpriteManager;
    public:
        static void PhysicsSpriteUpdate();
        void ReverseVelocity();
        Vector2 velocity;
        MovingSprite(float x, float y, float z, float width, float height, Vector2 velocity_p);
        ~MovingSprite(); 
};