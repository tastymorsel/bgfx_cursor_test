#include "asteroid.hpp"
#include <random>
#include <cmath>

Asteroid::Asteroid(Size size, const glm::vec2& position, const glm::vec2& velocity)
    : Entity(position, velocity, 0.0f, 1.0f)
    , size_(size)
    , rotationSpeed_(0.0f)
    , wobble_(0.0f)
    , wobbleSpeed_(0.0f) {
    
    InitializeForSize();
    GenerateVertices();
}

void Asteroid::InitializeForSize() {
    switch (size_) {
        case Size::LARGE:
            radius_ = LARGE_RADIUS;
            scale_ = 1.0f;
            rotationSpeed_ = 0.5f;
            wobbleSpeed_ = 2.0f;
            break;
        case Size::MEDIUM:
            radius_ = MEDIUM_RADIUS;
            scale_ = 0.7f;
            rotationSpeed_ = 1.0f;
            wobbleSpeed_ = 3.0f;
            break;
        case Size::SMALL:
            radius_ = SMALL_RADIUS;
            scale_ = 0.4f;
            rotationSpeed_ = 1.5f;
            wobbleSpeed_ = 4.0f;
            break;
    }
}

void Asteroid::GenerateVertices() {
    vertices_.clear();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.7f, 1.3f);
    
    const int numVertices = 8 + (int)size_ * 2;
    
    for (int i = 0; i < numVertices; ++i) {
        float angle = (2.0f * M_PI * i) / numVertices;
        float radius = radius_ * dist(gen);
        
        glm::vec2 vertex(
            cos(angle) * radius,
            sin(angle) * radius
        );
        
        vertices_.push_back(vertex);
    }
}

int Asteroid::GetPointValue() const {
    switch (size_) {
        case Size::LARGE: return LARGE_POINTS;
        case Size::MEDIUM: return MEDIUM_POINTS;
        case Size::SMALL: return SMALL_POINTS;
        default: return 0;
    }
}

bool Asteroid::CanBreak() const {
    return size_ != Size::SMALL;
}

void Asteroid::Update(float deltaTime) {
    // Update rotation
    rotation_ += rotationSpeed_ * deltaTime;
    
    // Update wobble
    wobble_ += wobbleSpeed_ * deltaTime;
    
    // Apply wobble to scale
    float wobbleScale = 1.0f + sin(wobble_) * 0.1f;
    scale_ = (size_ == Size::LARGE ? 1.0f : 
              size_ == Size::MEDIUM ? 0.7f : 0.4f) * wobbleScale;
    
    // Call base class update
    Entity::Update(deltaTime);
    
    // Wrap around screen
    WrapAround(1024.0f, 512.0f);
}

void Asteroid::Break() {
    // Mark for destruction
    active_ = false;
}

void Asteroid::OnCollision() {
    // Mark for destruction
    active_ = false;
}

glm::vec2 Asteroid::GetRandomVelocity() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(50.0f, 200.0f);
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * M_PI);
    
    float speed = speedDist(gen);
    float angle = angleDist(gen);
    
    return glm::vec2(cos(angle) * speed, sin(angle) * speed);
}