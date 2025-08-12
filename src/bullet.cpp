#include "bullet.hpp"
#include <cmath>

Bullet::Bullet(const glm::vec2& position, const glm::vec2& direction, float speed)
    : Entity(position, direction * speed, 0.0f, 1.0f)
    , direction_(direction)
    , speed_(speed)
    , lifetime_(BULLET_LIFETIME)
    , maxLifetime_(BULLET_LIFETIME) {
    
    radius_ = BULLET_RADIUS;
}

void Bullet::Update(float deltaTime) {
    // Update lifetime
    lifetime_ -= deltaTime;
    
    // Call base class update
    Entity::Update(deltaTime);
    
    // Wrap around screen
    WrapAround(1024.0f, 512.0f);
}

void Bullet::OnCollision() {
    // Mark for destruction
    active_ = false;
}