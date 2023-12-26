#version 330 core
in vec4 FragColor; // Input color from the vertex shader
out vec4 FinalColor; // Output variable for the final color

void main() {
    FinalColor = FragColor;
}