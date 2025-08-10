#include "entity.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Entity::Entity(const glm::vec2& position, const glm::vec2& velocity, float rotation, float scale)
    : position_(position)
    , velocity_(velocity)
    , rotation_(rotation)
    , scale_(scale)
    , radius_(10.0f)
    , active_(true) {
}

void Entity::Update(float deltaTime) {
    Move(deltaTime);
}

void Entity::Move(float deltaTime) {
    // Apply velocity
    position_ += velocity_ * deltaTime;
    
    // Apply friction
    velocity_ *= FRICTION;
    
    // Limit maximum speed
    float speed = glm::length(velocity_);
    if (speed > MAX_SPEED) {
        velocity_ = glm::normalize(velocity_) * MAX_SPEED;
    }
}

void Entity::WrapAround(float width, float height) {
    // Wrap around screen edges
    if (position_.x < -radius_) {
        position_.x = width + radius_;
    } else if (position_.x > width + radius_) {
        position_.x = -radius_;
    }
    
    if (position_.y < -radius_) {
        position_.y = height + radius_;
    } else if (position_.y > height + radius_) {
        position_.y = -radius_;
    }
}

bool Entity::CollidesWith(const Entity& other) const {
    if (!active_ || !other.active_) {
        return false;
    }
    
    float distance = GetDistanceTo(other);
    float minDistance = radius_ + other.radius_;
    
    return distance < minDistance;
}

float Entity::GetDistanceTo(const Entity& other) const {
    return glm::length(position_ - other.position_);
}