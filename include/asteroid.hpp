#pragma once

#include "entity.hpp"
#include <glm/glm.hpp>
#include <vector>

class Asteroid : public Entity {
public:
    enum class Size {
        LARGE,
        MEDIUM,
        SMALL
    };
    
    Asteroid(Size size, const glm::vec2& position, const glm::vec2& velocity);
    ~Asteroid() override = default;
    
    // Asteroid properties
    Size GetSize() const { return size_; }
    int GetPointValue() const;
    bool CanBreak() const;
    
    // Asteroid behavior
    void Update(float deltaTime) override;
    void Break();
    
    // Rendering
    const std::vector<glm::vec2>& GetVertices() const { return vertices_; }
    void GenerateVertices();
    
    // Collision response
    void OnCollision();
    
private:
    Size size_;
    std::vector<glm::vec2> vertices_;
    float rotationSpeed_;
    float wobble_;
    float wobbleSpeed_;
    
    // Size-specific constants
    static constexpr float LARGE_RADIUS = 40.0f;
    static constexpr float MEDIUM_RADIUS = 25.0f;
    static constexpr float SMALL_RADIUS = 15.0f;
    
    static constexpr float LARGE_SPEED = 100.0f;
    static constexpr float MEDIUM_SPEED = 150.0f;
    static constexpr float SMALL_SPEED = 200.0f;
    
    static constexpr int LARGE_POINTS = 20;
    static constexpr int MEDIUM_POINTS = 50;
    static constexpr int SMALL_POINTS = 100;
    
    // Helper methods
    void InitializeForSize();
    void GenerateRandomVertices();
    glm::vec2 GetRandomVelocity();
};