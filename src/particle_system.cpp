#include "particle_system.hpp"
#include <random>
#include <algorithm>
#include <cmath>

ParticleSystem::ParticleSystem() {
    particles_.reserve(MAX_PARTICLES);
}

void ParticleSystem::Update(float deltaTime) {
    for (auto& particle : particles_) {
        // Update position
        particle.position += particle.velocity * deltaTime;
        
        // Update rotation
        particle.rotation += particle.rotationSpeed * deltaTime;
        
        // Update life
        particle.life -= deltaTime;
        
        // Update size (shrink over time)
        particle.size *= 0.98f;
    }
    
    // Remove dead particles
    particles_.erase(
        std::remove_if(particles_.begin(), particles_.end(),
            [](const Particle& p) { return p.life <= 0.0f || p.size <= 0.1f; }),
        particles_.end()
    );
}

void ParticleSystem::Render() {
    // This would be implemented in the renderer
    // For now, just update particles
}

void ParticleSystem::CreateExplosion(const glm::vec2& position, int count, float power) {
    if (particles_.size() + count > MAX_PARTICLES) {
        count = MAX_PARTICLES - particles_.size();
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * M_PI);
    std::uniform_real_distribution<float> speedDist(power * 0.5f, power);
    std::uniform_real_distribution<float> lifeDist(0.5f, 1.5f);
    std::uniform_real_distribution<float> sizeDist(2.0f, 8.0f);
    
    for (int i = 0; i < count; ++i) {
        float angle = angleDist(gen);
        float speed = speedDist(gen);
        float life = lifeDist(gen);
        float size = sizeDist(gen);
        
        glm::vec2 velocity(
            cos(angle) * speed,
            sin(angle) * speed
        );
        
        glm::vec4 color(
            1.0f,                    // R
            0.5f + (gen() % 100) * 0.005f,  // G
            0.0f,                    // B
            1.0f                     // A
        );
        
        CreateParticle(position, velocity, color, life, size);
    }
}

void ParticleSystem::CreateThrust(const glm::vec2& position, const glm::vec2& direction) {
    if (particles_.size() >= MAX_PARTICLES) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(20.0f, 50.0f);
    std::uniform_real_distribution<float> lifeDist(0.2f, 0.5f);
    std::uniform_real_distribution<float> sizeDist(1.0f, 3.0f);
    
    // Create thrust particles behind the ship
    glm::vec2 thrustPos = position - direction * 25.0f;
    glm::vec2 velocity = -direction * speedDist(gen);
    
    glm::vec4 color(0.8f, 0.4f, 0.0f, 0.8f);
    float life = lifeDist(gen);
    float size = sizeDist(gen);
    
    CreateParticle(thrustPos, velocity, color, life, size);
}

void ParticleSystem::CreateHit(const glm::vec2& position, const glm::vec4& color) {
    if (particles_.size() >= MAX_PARTICLES) return;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDist(30.0f, 80.0f);
    std::uniform_real_distribution<float> lifeDist(0.3f, 0.8f);
    std::uniform_real_distribution<float> sizeDist(1.0f, 4.0f);
    
    for (int i = 0; i < 8; ++i) {
        float angle = (2.0f * M_PI * i) / 8.0f;
        float speed = speedDist(gen);
        float life = lifeDist(gen);
        float size = sizeDist(gen);
        
        glm::vec2 velocity(
            cos(angle) * speed,
            sin(angle) * speed
        );
        
        CreateParticle(position, velocity, color, life, size);
    }
}

void ParticleSystem::CreateParticle(const glm::vec2& position, const glm::vec2& velocity, 
                                   const glm::vec4& color, float life, float size) {
    Particle particle;
    particle.position = position;
    particle.velocity = velocity;
    particle.color = color;
    particle.life = life;
    particle.maxLife = life;
    particle.size = size;
    particle.rotation = 0.0f;
    particle.rotationSpeed = (rand() % 200 - 100) * 0.01f;
    
    particles_.push_back(particle);
}

void ParticleSystem::Clear() {
    particles_.clear();
}