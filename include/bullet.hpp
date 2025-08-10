#pragma once

#include "entity.hpp"
#include <glm/glm.hpp>

class Bullet : public Entity {
public:
    Bullet(const glm::vec2& position, const glm::vec2& direction, float speed);
    ~Bullet() override = default;
    
    // Bullet properties
    float GetLifetime() const { return lifetime_; }
    bool IsExpired() const { return lifetime_ <= 0.0f; }
    
    // Bullet behavior
    void Update(float deltaTime) override;
    void OnCollision();
    
    // Rendering
    const glm::vec2& GetDirection() const { return direction_; }
    
private:
    glm::vec2 direction_;
    float speed_;
    float lifetime_;
    float maxLifetime_;
    
    // Constants
    static constexpr float BULLET_RADIUS = 2.0f;
    static constexpr float BULLET_SPEED = 600.0f;
    static constexpr float BULLET_LIFETIME = 2.0f;
};