#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Input color attribute
out vec4 FragColor; // Output variable for passing color to the fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);
    FragColor = vec4(aColor, 1.0);
}