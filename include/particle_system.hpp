#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec4 color;
    float life;
    float maxLife;
    float size;
    float rotation;
    float rotationSpeed;
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem() = default;
    
    // Particle management
    void Update(float deltaTime);
    void Render();
    
    // Particle effects
    void CreateExplosion(const glm::vec2& position, int count, float power);
    void CreateThrust(const glm::vec2& position, const glm::vec2& direction);
    void CreateHit(const glm::vec2& position, const glm::vec4& color);
    
    // System management
    void Clear();
    int GetParticleCount() const { return particles_.size(); }
    
private:
    std::vector<Particle> particles_;
    
    // Particle creation helpers
    void CreateParticle(const glm::vec2& position, const glm::vec2& velocity, 
                       const glm::vec4& color, float life, float size);
    
    // Constants
    static constexpr int MAX_PARTICLES = 1000;
    static constexpr float EXPLOSION_POWER = 200.0f;
    static constexpr float THRUST_POWER = 50.0f;
    static constexpr float HIT_POWER = 100.0f;
};