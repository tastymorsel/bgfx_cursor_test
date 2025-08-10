#pragma once

#include "entity.hpp"
#include <glm/glm.hpp>

class Player : public Entity {
public:
    Player();
    ~Player() override = default;
    
    // Player-specific properties
    int GetLives() const { return lives_; }
    bool IsInvulnerable() const { return invulnerable_; }
    float GetInvulnerabilityTime() const { return invulnerabilityTime_; }
    
    // Player actions
    void TurnTowards(const glm::vec2& target);
    void Thrust(float deltaTime);
    void StopThrust();
    bool CanShoot() const;
    void SetShootCooldown(float cooldown);
    
    // State management
    void TakeDamage();
    void Respawn();
    void Update(float deltaTime) override;
    
    // Input handling
    void SetThrustInput(bool thrusting) { thrusting_ = thrusting; }
    void SetShootInput(bool shooting) { shooting_ = shooting; }
    
    // Getters for rendering
    const glm::vec2& GetThrustDirection() const { return thrustDirection_; }
    bool IsThrusting() const { return thrusting_; }
    
private:
    // Player state
    int lives_;
    bool invulnerable_;
    float invulnerabilityTime_;
    float shootCooldown_;
    
    // Movement
    bool thrusting_;
    glm::vec2 thrustDirection_;
    float thrustPower_;
    
    // Input state
    bool shooting_;
    
    // Constants
    static constexpr int STARTING_LIVES = 3;
    static constexpr float INVULNERABILITY_DURATION = 2.0f;
    static constexpr float SHOOT_COOLDOWN = 0.2f;
    static constexpr float THRUST_POWER = 300.0f;
    static constexpr float TURN_SPEED = 5.0f;
    static constexpr float PLAYER_RADIUS = 20.0f;
};