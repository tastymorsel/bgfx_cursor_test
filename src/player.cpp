#include "player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// Define M_PI if not available (Windows compatibility)
#ifndef M_PI
#define M_PI 3.14159265359
#endif

Player::Player()
    : Entity(glm::vec2(0.0f), glm::vec2(0.0f), 0.0f, 1.0f)
    , lives_(STARTING_LIVES)
    , invulnerable_(false)
    , invulnerabilityTime_(0.0f)
    , shootCooldown_(0.0f)
    , thrusting_(false)
    , thrustDirection_(0.0f, -1.0f)
    , thrustPower_(THRUST_POWER) {
    
    radius_ = PLAYER_RADIUS;
}

void Player::TurnTowards(const glm::vec2& target) {
    glm::vec2 direction = glm::normalize(target - position_);
    float targetRotation = atan2(direction.y, direction.x);
    
    // Smooth rotation towards target
    float rotationDiff = targetRotation - rotation_;
    
    // Normalize rotation difference to [-π, π]
    while (rotationDiff > M_PI) rotationDiff -= 2 * M_PI;
    while (rotationDiff < -M_PI) rotationDiff += 2 * M_PI;
    
    // Apply rotation with speed limit
    if (abs(rotationDiff) > 0.01f) {
        float rotationStep = TURN_SPEED * 0.016f; // Assuming 60 FPS
        if (abs(rotationDiff) < rotationStep) {
            rotation_ = targetRotation;
        } else {
            rotation_ += (rotationDiff > 0 ? rotationStep : -rotationStep);
        }
    }
    
    // Update thrust direction
    thrustDirection_ = glm::vec2(cos(rotation_), sin(rotation_));
}

void Player::Thrust(float deltaTime) {
    if (thrusting_) {
        velocity_ += thrustDirection_ * thrustPower_ * deltaTime;
    }
}

void Player::StopThrust() {
    thrusting_ = false;
}

bool Player::CanShoot() const {
    return shootCooldown_ <= 0.0f;
}

void Player::SetShootCooldown(float cooldown) {
    shootCooldown_ = cooldown;
}

void Player::TakeDamage() {
    if (!invulnerable_) {
        lives_--;
        invulnerable_ = true;
        invulnerabilityTime_ = INVULNERABILITY_DURATION;
    }
}

void Player::Respawn() {
    position_ = glm::vec2(0.0f);
    velocity_ = glm::vec2(0.0f);
    rotation_ = 0.0f;
    invulnerable_ = true;
    invulnerabilityTime_ = INVULNERABILITY_DURATION;
    shootCooldown_ = 0.0f;
    thrusting_ = false;
}

void Player::Update(float deltaTime) {
    // Update invulnerability timer
    if (invulnerable_) {
        invulnerabilityTime_ -= deltaTime;
        if (invulnerabilityTime_ <= 0.0f) {
            invulnerable_ = false;
        }
    }
    
    // Update shoot cooldown
    if (shootCooldown_ > 0.0f) {
        shootCooldown_ -= deltaTime;
    }
    
    // Apply thrust if active
    Thrust(deltaTime);
    
    // Call base class update
    Entity::Update(deltaTime);
    
    // Wrap around screen (assuming 1024x512)
    WrapAround(1024.0f, 512.0f);
}
