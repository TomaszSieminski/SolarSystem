#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;  // Dodaj normalne wektory

out vec2 TexCoord;
out vec3 FragPos;  // Dodaj fragment position
out vec3 Normal;   // Dodaj normal

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));  // Oblicz pozycjê fragmentu w przestrzeni œwiata
    Normal = mat3(transpose(inverse(model))) * aNormal;  // Oblicz normalê
    TexCoord = aTexCoord;
}
