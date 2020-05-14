#version 330 core
// layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

// out vec2 TexCoords;

// uniform mat4 model;
// uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

void main() {
    TexCoord = aTexCoord.xy;
	ourColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}
