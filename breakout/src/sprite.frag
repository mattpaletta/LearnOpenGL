#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
//out vec4 color;

//uniform sampler2D image;
//uniform vec3 spriteColor;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, TexCoord);
}
