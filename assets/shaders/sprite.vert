#version 330 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoord;

uniform mat4 u_transform;
uniform vec2 u_resolution;

out vec2 v_texCoord;
out vec2 v_worldPos;

void main() {
    vec4 worldPos = u_transform * vec4(a_position, 0.0, 1.0);
    v_worldPos = worldPos.xy;
    
    // Convert to screen coordinates
    vec2 screenPos = (worldPos.xy / u_resolution) * 2.0 - 1.0;
    gl_Position = vec4(screenPos, 0.0, 1.0);
    
    v_texCoord = a_texCoord;
}