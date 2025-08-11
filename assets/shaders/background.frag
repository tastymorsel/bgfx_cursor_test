#version 330 core

#define M_PI 3.14159265359

in vec2 v_texCoord;
out vec4 fragColor;

uniform vec4 u_time;

void main() {
    vec2 uv = v_texCoord;
    float time = u_time.x;
    
    // Create psychedelic space effect
    vec2 p = (uv - 0.5) * 2.0;
    float dist = length(p);
    
    // Rotating color wheel
    float angle = atan(p.y, p.x) + time * 0.5;
    float hue = (angle + M_PI) / (2.0 * M_PI);
    
    // Pulsing stars
    float stars = sin(dist * 50.0 - time * 3.0) * 0.5 + 0.5;
    stars *= exp(-dist * 2.0);
    
    // Color mixing
    vec3 color1 = vec3(0.5 + 0.5 * cos(hue * 6.28318 + 0.0), 
                        0.5 + 0.5 * cos(hue * 6.28318 + 2.094), 
                        0.5 + 0.5 * cos(hue * 6.28318 + 4.188));
    
    vec3 color2 = vec3(0.5 + 0.5 * cos(hue * 6.28318 + 1.0), 
                        0.5 + 0.5 * cos(hue * 6.28318 + 3.141), 
                        0.5 + 0.5 * cos(hue * 6.28318 + 5.236));
    
    vec3 finalColor = mix(color1, color2, stars);
    finalColor += stars * 0.3;
    
    fragColor = vec4(finalColor, 1.0);
}