#include "game.hpp"
#include <algorithm>
#include <random>
#include <iostream>

Game::Game() 
    : state_(GameState::MENU)
    , score_(0)
    , lives_(3)
    , wave_(1)
    , waveTimer_(0.0f)
    , lastFrame_(std::chrono::high_resolution_clock::now()) {
}

Game::~Game() {
    Shutdown();
}

bool Game::Initialize() {
    // Initialize renderer
    renderer_ = std::make_unique<Renderer>();
    if (!renderer_->Initialize(nullptr, 1024, 512)) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return false;
    }
    
    // Initialize audio
    audio_ = std::make_unique<Audio>();
    if (!audio_->Initialize()) {
        std::cerr << "Failed to initialize audio" << std::endl;
        return false;
    }
    
    // Initialize player
    player_ = std::make_unique<Player>();
    
    // Initialize particle system
    particles_ = std::make_unique<ParticleSystem>();
    
    // Start background music
    audio_->PlayBackgroundMusic();
    
    // Set initial state
    state_ = GameState::PLAYING;
    
    return true;
}

void Game::Run() {
    auto now = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(now - lastFrame_).count();
    lastFrame_ = now;
    
    // Cap delta time to prevent large jumps
    deltaTime = std::min(deltaTime, 0.016f);
    
    ProcessInput();
    UpdateGame(deltaTime);
    Render();
}

void Game::Shutdown() {
    if (audio_) {
        audio_->Shutdown();
    }
    if (renderer_) {
        renderer_->Shutdown();
    }
}

void Game::ProcessInput() {
    // Input is handled via GLFW callbacks
}

void Game::UpdateGame(float deltaTime) {
    if (state_ != GameState::PLAYING) {
        return;
    }
    
    // Update player
    if (player_) {
        player_->Update(deltaTime);
    }
    
    // Update asteroids
    for (auto& asteroid : asteroids_) {
        if (asteroid && asteroid->IsActive()) {
            asteroid->Update(deltaTime);
        }
    }
    
    // Update bullets
    for (auto& bullet : bullets_) {
        if (bullet && bullet->IsActive()) {
            bullet->Update(deltaTime);
        }
    }
    
    // Update particles
    if (particles_) {
        particles_->Update(deltaTime);
    }
    
    // Handle collisions
    HandleCollisions();
    
    // Clean up destroyed entities
    CleanupDestroyedEntities();
    
    // Spawn new waves
    waveTimer_ += deltaTime;
    if (waveTimer_ >= ASTEROID_SPAWN_INTERVAL) {
        SpawnAsteroidWave();
        waveTimer_ = 0.0f;
    }
    
    // Check win/lose conditions
    if (lives_ <= 0) {
        state_ = GameState::GAME_OVER;
        audio_->PlayPlayerDeathSound();
    }
    
    if (asteroids_.empty() && state_ == GameState::PLAYING) {
        wave_++;
        SpawnAsteroidWave();
    }
}

void Game::HandleCollisions() {
    // Player vs Asteroid collisions
    if (player_ && player_->IsActive() && !player_->IsInvulnerable()) {
        for (auto& asteroid : asteroids_) {
            if (asteroid && asteroid->IsActive() && player_->CollidesWith(*asteroid)) {
                player_->TakeDamage();
                lives_--;
                audio_->PlayPlayerDeathSound();
                
                // Create explosion particles
                if (particles_) {
                    particles_->CreateExplosion(player_->GetPosition(), 50, 100.0f);
                }
                
                break;
            }
        }
    }
    
    // Bullet vs Asteroid collisions
    for (auto& bullet : bullets_) {
        if (!bullet || !bullet->IsActive()) continue;
        
        for (auto& asteroid : asteroids_) {
            if (!asteroid || !asteroid->IsActive()) continue;
            
            if (bullet->CollidesWith(*asteroid)) {
                // Handle bullet hit
                bullet->OnCollision();
                asteroid->OnCollision();
                
                // Increase score
                score_ += asteroid->GetPointValue();
                
                // Play hit sound
                audio_->PlayAsteroidHitSound();
                
                // Create hit particles
                if (particles_) {
                    particles_->CreateHit(asteroid->GetPosition(), glm::vec4(1.0f, 0.8f, 0.0f, 1.0f));
                }
                
                // Break asteroid if possible
                if (asteroid->CanBreak()) {
                    asteroid->Break();
                    
                    // Create smaller asteroids
                    Asteroid::Size newSize;
                    switch (asteroid->GetSize()) {
                        case Asteroid::Size::LARGE:
                            newSize = Asteroid::Size::MEDIUM;
                            break;
                        case Asteroid::Size::MEDIUM:
                            newSize = Asteroid::Size::SMALL;
                            break;
                        default:
                            newSize = Asteroid::Size::SMALL;
                            break;
                    }
                    
                    // Spawn smaller asteroids
                    for (int i = 0; i < 2; ++i) {
                        glm::vec2 offset = glm::vec2(
                            (rand() % 100 - 50) * 0.1f,
                            (rand() % 100 - 50) * 0.1f
                        );
                        
                        auto newAsteroid = std::make_unique<Asteroid>(
                            newSize,
                            asteroid->GetPosition() + offset,
                            asteroid->GetVelocity() + offset * 50.0f
                        );
                        asteroids_.push_back(std::move(newAsteroid));
                    }
                } else {
                    // Final explosion
                    if (particles_) {
                        particles_->CreateExplosion(asteroid->GetPosition(), 30, 80.0f);
                    }
                    audio_->PlayExplosionSound();
                }
                
                break;
            }
        }
    }
}

void Game::SpawnAsteroidWave() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> velDist(-100.0f, 100.0f);
    
    for (int i = 0; i < ASTEROIDS_PER_WAVE + wave_; ++i) {
        glm::vec2 position;
        glm::vec2 velocity;
        
        // Spawn asteroids around the edges
        if (i % 4 == 0) {
            position = glm::vec2(-1.0f, posDist(gen));
        } else if (i % 4 == 1) {
            position = glm::vec2(1.0f, posDist(gen));
        } else if (i % 4 == 2) {
            position = glm::vec2(posDist(gen), -1.0f);
        } else {
            position = glm::vec2(posDist(gen), 1.0f);
        }
        
        // Scale position to screen coordinates
        position *= glm::vec2(renderer_->GetWidth() * 0.5f, renderer_->GetHeight() * 0.5f);
        
        velocity = glm::vec2(velDist(gen), velDist(gen));
        
        auto asteroid = std::make_unique<Asteroid>(Asteroid::Size::LARGE, position, velocity);
        asteroids_.push_back(std::move(asteroid));
    }
}

void Game::UpdateEntities(float deltaTime) {
    // This is now handled in UpdateGame
}

void Game::Render() {
    if (!renderer_) return;
    
    renderer_->BeginFrame();
    
    // Render background
    static float time = 0.0f;
    time += 0.016f; // Approximate frame time
    renderer_->RenderBackground(time);
    
    // Render game entities
    if (state_ == GameState::PLAYING) {
        // Render player
        if (player_ && player_->IsActive()) {
            uint32_t color = player_->IsInvulnerable() ? 0x808080FF : 0x00FF00FF;
            renderer_->RenderSprite(player_->GetPosition(), player_->GetRotation(), 1.0f, color);
        }
        
        // Render asteroids
        for (auto& asteroid : asteroids_) {
            if (asteroid && asteroid->IsActive()) {
                renderer_->RenderSprite(asteroid->GetPosition(), asteroid->GetRotation(), asteroid->GetScale(), 0x8B4513FF);
            }
        }
        
        // Render bullets
        for (auto& bullet : bullets_) {
            if (bullet && bullet->IsActive()) {
                renderer_->RenderSprite(bullet->GetPosition(), 0.0f, 0.5f, 0xFFFF00FF);
            }
        }
        
        // Render particles
        if (particles_) {
            particles_->Render();
        }
    }
    
    // Render UI
    renderer_->RenderUI();
    
    // Render score
    std::string scoreText = "Score: " + std::to_string(score_);
    renderer_->RenderText(scoreText, glm::vec2(10, 10), 1.0f, 0xFFFFFFFF);
    
    // Render lives
    std::string livesText = "Lives: " + std::to_string(lives_);
    renderer_->RenderText(livesText, glm::vec2(10, 40), 1.0f, 0xFFFFFFFF);
    
    // Render wave
    std::string waveText = "Wave: " + std::to_string(wave_);
    renderer_->RenderText(waveText, glm::vec2(10, 70), 1.0f, 0xFFFFFFFF);
    
    // Render game over screen
    if (state_ == GameState::GAME_OVER) {
        renderer_->RenderText("GAME OVER", glm::vec2(renderer_->GetWidth() * 0.5f - 100, renderer_->GetHeight() * 0.5f), 2.0f, 0xFF0000FF);
        renderer_->RenderText("Press R to restart", glm::vec2(renderer_->GetWidth() * 0.5f - 100, renderer_->GetHeight() * 0.5f + 50), 1.0f, 0xFFFFFFFF);
    }
    
    renderer_->EndFrame();
}

void Game::SpawnBullet() {
    if (!player_ || !player_->CanShoot() || bullets_.size() >= MAX_BULLETS) {
        return;
    }
    
    glm::vec2 direction = glm::vec2(
        cos(player_->GetRotation()),
        sin(player_->GetRotation())
    );
    
    auto bullet = std::make_unique<Bullet>(
        player_->GetPosition() + direction * 30.0f,
        direction,
        600.0f
    );
    
    bullets_.push_back(std::move(bullet));
    
    // Play shoot sound
    audio_->PlayShootSound();
    
    // Set shoot cooldown
    player_->SetShootCooldown(0.2f);
}

void Game::CleanupDestroyedEntities() {
    // Remove inactive asteroids
    asteroids_.erase(
        std::remove_if(asteroids_.begin(), asteroids_.end(),
            [](const std::unique_ptr<Asteroid>& asteroid) {
                return !asteroid || !asteroid->IsActive();
            }),
        asteroids_.end()
    );
    
    // Remove inactive bullets
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
            [](const std::unique_ptr<Bullet>& bullet) {
                return !bullet || !bullet->IsActive() || bullet->IsExpired();
            }),
        bullets_.end()
    );
}

void Game::OnMouseMove(double x, double y) {
    if (player_ && state_ == GameState::PLAYING) {
        glm::vec2 mousePos(x, y);
        player_->TurnTowards(mousePos);
    }
}

void Game::OnMouseButton(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (state_ == GameState::PLAYING) {
            SpawnBullet();
        }
    }
}

void Game::ResetGame() {
    score_ = 0;
    lives_ = 3;
    wave_ = 1;
    waveTimer_ = 0.0f;
    
    asteroids_.clear();
    bullets_.clear();
    
    if (player_) {
        player_->Respawn();
    }
    
    if (particles_) {
        particles_->Clear();
    }
    
    state_ = GameState::PLAYING;
}