#version 330 core

in vec2 v_texCoord;
out vec4 fragColor;

uniform vec4 u_color;

void main() {
    // Simple sprite rendering with color tinting
    vec4 spriteColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    // Apply color uniform
    fragColor = spriteColor * u_color;
}