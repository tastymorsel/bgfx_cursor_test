#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity {
public:
    Entity(const glm::vec2& position = glm::vec2(0.0f), 
           const glm::vec2& velocity = glm::vec2(0.0f),
           float rotation = 0.0f,
           float scale = 1.0f);
    virtual ~Entity() = default;
    
    // Core properties
    const glm::vec2& GetPosition() const { return position_; }
    const glm::vec2& GetVelocity() const { return velocity_; }
    float GetRotation() const { return rotation_; }
    float GetScale() const { return scale_; }
    float GetRadius() const { return radius_; }
    bool IsActive() const { return active_; }
    
    // Setters
    void SetPosition(const glm::vec2& pos) { position_ = pos; }
    void SetVelocity(const glm::vec2& vel) { velocity_ = vel; }
    void SetRotation(float rot) { rotation_ = rot; }
    void SetScale(float s) { scale_ = s; }
    void SetRadius(float r) { radius_ = r; }
    void SetActive(bool active) { active_ = active; }
    
    // Physics and movement
    virtual void Update(float deltaTime);
    virtual void Move(float deltaTime);
    void WrapAround(float width, float height);
    
    // Collision detection
    bool CollidesWith(const Entity& other) const;
    float GetDistanceTo(const Entity& other) const;
    
    // Lifecycle
    virtual void OnDestroy() {}
    
protected:
    glm::vec2 position_;
    glm::vec2 velocity_;
    float rotation_;
    float scale_;
    float radius_;
    bool active_;
    
    // Physics constants
    static constexpr float MAX_SPEED = 500.0f;
    static constexpr float FRICTION = 0.98f;
};