#include "audio.hpp"
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

// Define M_PI if not available (Windows compatibility)
#ifndef M_PI
#define M_PI 3.14159265359
#endif

Audio::Audio()
    : masterVolume_(1.0f)
    , sfxVolume_(1.0f)
    , musicVolume_(0.7f) {
    
    // Initialize miniaudio engine
    if (!g_audioEngine.init()) {
        std::cerr << "Failed to initialize miniaudio engine" << std::endl;
        return;
    }
    
    // Generate audio buffers
    GenerateShootTone(SHOOT_FREQ, 0.1f);
    GenerateExplosionNoise(EXPLOSION_DURATION);
    GenerateHitTone(HIT_FREQ, HIT_DURATION);
}

Audio::~Audio() {
    Shutdown();
}

bool Audio::Initialize() {
    // Audio engine is already initialized in constructor
    return true;
}

void Audio::Shutdown() {
    g_audioEngine.uninit();
}

void Audio::PlayShootSound() {
    PlayBuffer(shootBuffer_, sfxVolume_ * masterVolume_);
}

void Audio::PlayExplosionSound() {
    PlayBuffer(explosionBuffer_, sfxVolume_ * masterVolume_);
}

void Audio::PlayAsteroidHitSound() {
    PlayBuffer(hitBuffer_, sfxVolume_ * masterVolume_);
}

void Audio::PlayPlayerDeathSound() {
    // Play a longer, lower pitched explosion
    std::vector<float> deathBuffer;
    GenerateExplosionNoise(0.8f);
    PlayBuffer(explosionBuffer_, sfxVolume_ * masterVolume_);
}

void Audio::PlayBackgroundMusic() {
    // For now, just play ambient tones
    // In a full implementation, this would loop continuously
}

void Audio::StopBackgroundMusic() {
    // Stop any looping audio
}

void Audio::SetMusicVolume(float volume) {
    musicVolume_ = std::max(0.0f, std::min(volume, 1.0f));
}

void Audio::GenerateShootTone(float frequency, float duration) {
    GenerateTone(shootBuffer_, frequency, duration, 0.3f);
}

void Audio::GenerateExplosionNoise(float duration) {
    GenerateNoise(explosionBuffer_, duration, 0.5f);
}

void Audio::GenerateHitTone(float frequency, float duration) {
    GenerateTone(hitBuffer_, frequency, duration, 0.4f);
}

void Audio::SetMasterVolume(float volume) {
    masterVolume_ = std::max(0.0f, std::min(volume, 1.0f));
}

void Audio::SetSFXVolume(float volume) {
    sfxVolume_ = std::max(0.0f, std::min(volume, 1.0f));
}

void Audio::GenerateSineWave(std::vector<float>& buffer, float frequency, float duration, float amplitude) {
    int numSamples = static_cast<int>(SAMPLE_RATE * duration);
    buffer.resize(numSamples);
    
    for (int i = 0; i < numSamples; ++i) {
        float t = static_cast<float>(i) / SAMPLE_RATE;
        buffer[i] = amplitude * sin(2.0f * M_PI * frequency * t);
    }
}

void Audio::GenerateNoise(std::vector<float>& buffer, float duration, float amplitude) {
    int numSamples = static_cast<int>(SAMPLE_RATE * duration);
    buffer.resize(numSamples);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = amplitude * dist(gen);
        
        // Apply envelope (fade out)
        float envelope = 1.0f - (static_cast<float>(i) / numSamples);
        buffer[i] *= envelope;
    }
}

void Audio::GenerateTone(std::vector<float>& buffer, float frequency, float duration, float amplitude) {
    int numSamples = static_cast<int>(SAMPLE_RATE * duration);
    buffer.resize(numSamples);
    
    for (int i = 0; i < numSamples; ++i) {
        float t = static_cast<float>(i) / SAMPLE_RATE;
        
        // Generate tone with harmonics for more interesting sound
        float tone = 0.0f;
        tone += 0.6f * sin(2.0f * M_PI * frequency * t);
        tone += 0.3f * sin(2.0f * M_PI * frequency * 2.0f * t);
        tone += 0.1f * sin(2.0f * M_PI * frequency * 3.0f * t);
        
        buffer[i] = amplitude * tone;
        
        // Apply envelope (quick attack, slow decay)
        float envelope = 1.0f;
        if (i < numSamples * 0.1f) {
            // Attack
            envelope = static_cast<float>(i) / (numSamples * 0.1f);
        } else {
            // Decay
            float decayStart = numSamples * 0.1f;
            float decayProgress = (i - decayStart) / (numSamples - decayStart);
            envelope = 1.0f - decayProgress * 0.8f;
        }
        
        buffer[i] *= envelope;
    }
}

void Audio::PlayBuffer(const std::vector<float>& buffer, float volume) {
    // In a full implementation, this would queue the audio data
    // For now, we'll just simulate playback
    
    // Apply volume
    std::vector<float> scaledBuffer = buffer;
    for (auto& sample : scaledBuffer) {
        sample *= volume;
    }
    
    // In a real implementation, this would send data to the audio device
    // ma_device_write(&device_, scaledBuffer.data(), scaledBuffer.size());
}