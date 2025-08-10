#pragma once

#include <miniaudio.h>
#include <vector>
#include <memory>
#include <string>

class Audio {
public:
    Audio();
    ~Audio();
    
    bool Initialize();
    void Shutdown();
    
    // Sound effects
    void PlayShootSound();
    void PlayExplosionSound();
    void PlayAsteroidHitSound();
    void PlayPlayerDeathSound();
    
    // Music and ambient
    void PlayBackgroundMusic();
    void StopBackgroundMusic();
    void SetMusicVolume(float volume);
    
    // Procedural audio generation
    void GenerateShootTone(float frequency, float duration);
    void GenerateExplosionNoise(float duration);
    void GenerateHitTone(float frequency, float duration);
    
    // Audio settings
    void SetMasterVolume(float volume);
    void SetSFXVolume(float volume);
    float GetMasterVolume() const { return masterVolume_; }
    float GetSFXVolume() const { return sfxVolume_; }
    
private:
    // Miniaudio context
    ma_context context_;
    ma_device device_;
    
    // Audio buffers for procedural generation
    std::vector<float> shootBuffer_;
    std::vector<float> explosionBuffer_;
    std::vector<float> hitBuffer_;
    
    // Volume controls
    float masterVolume_;
    float sfxVolume_;
    float musicVolume_;
    
    // Audio generation helpers
    void GenerateSineWave(std::vector<float>& buffer, float frequency, float duration, float amplitude);
    void GenerateNoise(std::vector<float>& buffer, float duration, float amplitude);
    void GenerateTone(std::vector<float>& buffer, float frequency, float duration, float amplitude);
    
    // Audio playback helpers
    void PlayBuffer(const std::vector<float>& buffer, float volume);
    
    // Constants
    static constexpr int SAMPLE_RATE = 44100;
    static constexpr float SHOOT_FREQ = 800.0f;
    static constexpr float EXPLOSION_DURATION = 0.3f;
    static constexpr float HIT_FREQ = 400.0f;
    static constexpr float HIT_DURATION = 0.1f;
};