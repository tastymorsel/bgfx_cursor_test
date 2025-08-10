#version 330 core

in vec2 v_texCoord;
in vec2 v_worldPos;

out vec4 fragColor;

uniform vec4 u_color;
uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_lightPos;
uniform float u_lightIntensity;

// Simple lighting calculation
float calculateLighting(vec2 worldPos, vec2 lightPos, float intensity) {
    float distance = length(worldPos - lightPos);
    float attenuation = 1.0 / (1.0 + distance * 0.01);
    return attenuation * intensity;
}

// Glow effect based on distance from center
float calculateGlow(vec2 worldPos) {
    vec2 center = u_resolution * 0.5;
    float distance = length(worldPos - center);
    float maxDistance = length(u_resolution * 0.5);
    return 1.0 - smoothstep(0.0, maxDistance, distance);
}

void main() {
    // Base color from uniform
    vec4 baseColor = u_color;
    
    // Calculate lighting
    float light = calculateLighting(v_worldPos, u_lightPos, u_lightIntensity);
    
    // Add glow effect
    float glow = calculateGlow(v_worldPos);
    
    // Create pulsing effect
    float pulse = sin(u_time * 2.0) * 0.1 + 0.9;
    
    // Combine all effects
    vec3 finalColor = baseColor.rgb * light * pulse;
    finalColor += baseColor.rgb * glow * 0.3;
    
    // Add subtle rim lighting
    float rim = 1.0 - abs(dot(normalize(v_worldPos - u_resolution * 0.5), vec2(0.0, 1.0)));
    finalColor += baseColor.rgb * rim * 0.2;
    
    // Ensure we don't exceed maximum brightness
    finalColor = min(finalColor, 1.0);
    
    fragColor = vec4(finalColor, baseColor.a);
}