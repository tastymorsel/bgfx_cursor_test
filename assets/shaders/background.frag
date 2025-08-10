#version 330 core

in vec2 v_texCoord;
out vec4 fragColor;

uniform float u_time;

// Noise functions for procedural generation
float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);
    
    float a = hash(i);
    float b = hash(i + vec2(1.0, 0.0));
    float c = hash(i + vec2(0.0, 1.0));
    float d = hash(i + vec2(1.0, 1.0));
    
    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);
}

float fbm(vec2 p) {
    float value = 0.0;
    float amplitude = 0.5;
    float frequency = 1.0;
    
    for(int i = 0; i < 5; i++) {
        value += amplitude * noise(p * frequency);
        amplitude *= 0.5;
        frequency *= 2.0;
    }
    
    return value;
}

void main() {
    vec2 uv = v_texCoord;
    
    // Create multiple layers of noise for depth
    float noise1 = fbm(uv * 3.0 + u_time * 0.1);
    float noise2 = fbm(uv * 6.0 + u_time * 0.2);
    float noise3 = fbm(uv * 12.0 + u_time * 0.3);
    
    // Combine noise layers
    float combined = (noise1 * 0.5 + noise2 * 0.3 + noise3 * 0.2);
    
    // Create psychedelic color variations
    vec3 color1 = vec3(0.1, 0.0, 0.3); // Deep purple
    vec3 color2 = vec3(0.0, 0.2, 0.4); // Deep blue
    vec3 color3 = vec3(0.3, 0.0, 0.2); // Magenta
    
    // Animate colors based on time and position
    float colorMix = sin(u_time * 0.5 + uv.x * 10.0) * 0.5 + 0.5;
    vec3 baseColor = mix(color1, color2, colorMix);
    
    // Add star field effect
    float stars = pow(noise(uv * 50.0), 20.0);
    stars *= sin(u_time + uv.x * 100.0) * 0.5 + 0.5;
    
    // Create nebula-like swirls
    float swirl = sin(uv.x * 8.0 + u_time * 0.3) * cos(uv.y * 6.0 + u_time * 0.2);
    swirl *= noise(uv * 4.0 + u_time * 0.1);
    
    // Combine all effects
    vec3 finalColor = baseColor * (0.3 + combined * 0.7);
    finalColor += stars * vec3(1.0, 1.0, 0.8) * 0.5;
    finalColor += swirl * color3 * 0.3;
    
    // Add subtle pulsing
    float pulse = sin(u_time * 0.8) * 0.1 + 0.9;
    finalColor *= pulse;
    
    fragColor = vec4(finalColor, 1.0);
}