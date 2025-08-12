#pragma once

#include <memory>
#include <vector>
#include <chrono>
#include "renderer.hpp"
#include "audio.hpp"
#include "player.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"
#include "particle_system.hpp"

class Game {
public:
    Game();
    ~Game();
    
    bool Initialize();
    void Run();
    void Shutdown();
    
    // Game state
    enum class GameState {
        MENU,
        PLAYING,
        GAME_OVER
    };
    
    GameState GetState() const { return state_; }
    void SetState(GameState state) { state_ = state; }
    
    // Game mechanics
    void SpawnAsteroidWave();
    void UpdateGame(float deltaTime);
    void HandleCollisions();
    void ResetGame();
    
    // Input handling
    void OnMouseMove(double x, double y);
    void OnMouseButton(int button, int action);
    
    // Getters
    int GetScore() const { return score_; }
    int GetLives() const { return lives_; }
    const std::vector<std::unique_ptr<Asteroid>>& GetAsteroids() const { return asteroids_; }
    const std::vector<std::unique_ptr<Bullet>>& GetBullets() const { return bullets_; }
    
private:
    // Core systems
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<Audio> audio_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<ParticleSystem> particles_;
    
    // Game entities
    std::vector<std::unique_ptr<Asteroid>> asteroids_;
    std::vector<std::unique_ptr<Bullet>> bullets_;
    
    // Game state
    GameState state_;
    int score_;
    int lives_;
    int wave_;
    float waveTimer_;
    
    // Timing
    std::chrono::high_resolution_clock::time_point lastFrame_;
    
    // Game constants
    static constexpr float ASTEROID_SPAWN_INTERVAL = 5.0f;
    static constexpr int ASTEROIDS_PER_WAVE = 5;
    static constexpr int MAX_BULLETS = 10;
    
    void ProcessInput();
    void UpdateEntities(float deltaTime);
    void Render();
    void SpawnBullet();
    void CleanupDestroyedEntities();
};