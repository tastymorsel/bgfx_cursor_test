#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace ma {
    // Audio device types
    enum DeviceType {
        Playback,
        Capture,
        Duplex
    };
    
    // Audio format types
    enum Format {
        FormatUnknown,
        FormatU8,
        FormatS16,
        FormatS24,
        FormatS32,
        FormatF32
    };
    
    // Audio device configuration
    struct DeviceConfig {
        DeviceType deviceType;
        Format format;
        uint32_t sampleRate;
        uint32_t channels;
        uint32_t bufferSize;
    };
    
    // Audio device
    class Device {
    public:
        Device() : isInitialized(false) {}
        ~Device() { uninit(); }
        
        bool init(const DeviceConfig& config);
        void uninit();
        bool isInitialized;
        
        // Audio playback
        bool write(const void* data, uint32_t frameCount);
        void setVolume(float volume);
        float getVolume() const { return volume; }
        
    private:
        float volume;
        DeviceConfig config;
    };
    
    // Sound effect
    class Sound {
    public:
        Sound() : isLoaded(false) {}
        ~Sound() { unload(); }
        
        bool load(const std::string& filename);
        void unload();
        bool isLoaded;
        
        // Playback
        void play();
        void stop();
        void setVolume(float volume);
        float getVolume() const { return volume; }
        
    private:
        float volume;
        std::vector<uint8_t> audioData;
        uint32_t sampleRate;
        uint32_t channels;
        Format format;
    };
    
    // Audio engine
    class Engine {
    public:
        Engine() : isInitialized(false) {}
        ~Engine() { uninit(); }
        
        bool init();
        void uninit();
        bool isInitialized;
        
        // Device management
        Device* createDevice(const DeviceConfig& config);
        void destroyDevice(Device* device);
        
        // Sound management
        Sound* createSound(const std::string& filename);
        void destroySound(Sound* sound);
        
        // Global audio settings
        void setMasterVolume(float volume);
        float getMasterVolume() const { return masterVolume; }
        
    private:
        float masterVolume;
        std::vector<Device*> devices;
        std::vector<Sound*> sounds;
    };
    
    // Utility functions
    namespace utils {
        // Generate procedural audio
        std::vector<float> generateTone(float frequency, float duration, float sampleRate);
        std::vector<float> generateNoise(float duration, float sampleRate);
        std::vector<float> generateExplosion(float duration, float sampleRate);
        
        // Audio processing
        void applyEnvelope(std::vector<float>& audio, float attack, float decay, float sustain, float release);
        void applyFilter(std::vector<float>& audio, float cutoff, float resonance);
        void applyReverb(std::vector<float>& audio, float roomSize, float damping);
    }
}

// Global audio engine instance
extern ma::Engine g_audioEngine;