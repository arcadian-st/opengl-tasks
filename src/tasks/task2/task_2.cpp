// Task 2: Drawing Basic Shapes
// 1. Drawing a Triangle:
// Create a simple vertex and fragment shader.
// Render a colored triangle using OpenGL.
// 2. Drawing a Rectangle:
// Expand your program to draw a colored rectangle.
// 3. Drawing Basic Shapes:
// Experiment with drawing other basic shapes like circles or lines.

// Modularize the process by creating a function for shader initialization
// and another function for rendering a shape.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

// Function to set up the window
GLFWwindow* setupWindow() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
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
        return nullptr;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    return window;
};

// Function to initialize shaders
unsigned int initializeShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
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

    return shaderProgram;
}

// Function to render a shape
void renderShape(unsigned int VAO, unsigned int shaderProgram, int verticesCount) {
    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the shape
    glDrawArrays(GL_TRIANGLE_FAN, 0, verticesCount);

    // Unbind the VAO
    glBindVertexArray(0);
}

struct shape_output
{
    unsigned int VAO;
    unsigned int VBO;
};

// Function to set up a VAO and VBO for a shape
shape_output setupShape(const float* vertices, int verticesCount) {
    // Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind and set vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return shape_output{VAO, VBO};
}

// Main function to display a triangle
int main_triangle() {
    GLFWwindow* window = setupWindow();
    if (!window) {
        return -1;
    }

    float vertices_triangle[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    // Create shader program and VAO, VBO for the triangle
    unsigned int shaderProgram = initializeShaders(vertexShaderSource, fragmentShaderSource);
    auto [VAO_triangle, VBO_triangle] = setupShape(vertices_triangle, 6);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the triangle
        renderShape(VAO_triangle, shaderProgram, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO_triangle);
    glDeleteBuffers(1, &VBO_triangle);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

// Main function to display a rectangle
int main_rectangle() {
    GLFWwindow* window = setupWindow();
    if (!window) {
        return -1;
    }

    float vertices_rectangle[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    // Create shader program and VAO, VBO for the rectangle
    unsigned int shaderProgram = initializeShaders(vertexShaderSource, fragmentShaderSource);
    auto [VAO_rectangle, VBO_rectangle] = setupShape(vertices_rectangle, 8);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the rectangle
        renderShape(VAO_rectangle, shaderProgram, 4);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO_rectangle);
    glDeleteBuffers(1, &VBO_rectangle);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

// Main function to display a triangle and a rectangle side by side
int main_two_shapes() {
    GLFWwindow* window = setupWindow();
    if (!window) {
        return -1;
    }

    float vertices_triangle[] = {
        -1.0f, -0.5f,
         0.0f, -0.5f,
        -0.5f,  0.5f
    };

    float vertices_rectangle[] = {
        1.0f, -0.5f,
        0.0f, -0.5f,
        0.0f,  0.5f,
        1.0f,  0.5f
    };

    // Create shader program
    unsigned int shaderProgram = initializeShaders(vertexShaderSource, fragmentShaderSource);

    // create VAO, VBO for the triangle
    auto [VAO_triangle, VBO_triangle] = setupShape(vertices_triangle, 6);
    
    // create VAO, VBO for the rectangle
    auto [VAO_rectangle, VBO_rectangle] = setupShape(vertices_rectangle, 8);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the triangle
        renderShape(VAO_triangle, shaderProgram, 3);

        // Render the rectangle
        renderShape(VAO_rectangle, shaderProgram, 4);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO_triangle);
    glDeleteBuffers(1, &VBO_triangle);
    glDeleteVertexArrays(1, &VAO_rectangle);
    glDeleteBuffers(1, &VBO_rectangle);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}

int main_task_2() {
    // Call one of the main functions based on your requirement
    // main_triangle();
    // main_rectangle();
    main_two_shapes();

    return 0;
}
