// Task 2: Drawing Basic Shapes
// 1. Drawing a Triangle:
// Create a simple vertex and fragment shader.
// Render a colored triangle using OpenGL.
// 2. Drawing a Rectangle:
// Expand your program to draw a colored rectangle.
// 3. Drawing Basic Shapes:
// Experiment with drawing other basic shapes like circles or lines.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main_task_2_3() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int width = 800, height = 600;

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Load and compile shaders
    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    // Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    // Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
    }

    // Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex data for circle lines
    const int numSegments = 36;
    float vertices_circle_lines[numSegments * 2];
    const float ratio = static_cast<float>(width) / static_cast<float>(height);

    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(numSegments);
        vertices_circle_lines[i * 2] = 0.5f * cos(theta); // X coordinate
        vertices_circle_lines[i * 2 + 1] = 0.5f * sin(theta) * ratio; // Y coordinate
    }

    // Vertex Array Object (VAO) and Vertex Buffer Object (VBO) for circle lines
    unsigned int VAO_circle_lines, VBO_circle_lines;
    glGenVertexArrays(1, &VAO_circle_lines);
    glGenBuffers(1, &VBO_circle_lines);

    // Bind the VAO for circle lines
    glBindVertexArray(VAO_circle_lines);

    // Bind and set vertex buffer for circle lines
    glBindBuffer(GL_ARRAY_BUFFER, VBO_circle_lines);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_circle_lines), vertices_circle_lines, GL_STATIC_DRAW);

    // Set the vertex attribute pointers for circle lines
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO for circle lines
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Set the line width
    glLineWidth(2.0f);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program for the rectangle
        glUseProgram(shaderProgram);

        // Bind the VAO for circle lines
        glBindVertexArray(VAO_circle_lines);

        // Draw the circle lines
        glDrawArrays(GL_LINE_LOOP, 0, numSegments);

        // Unbind VAO for circle lines
        glBindVertexArray(0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO_circle_lines);
    glDeleteBuffers(1, &VBO_circle_lines);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
