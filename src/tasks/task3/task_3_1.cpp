// Task 3: Transformations
// 1. 2D Transformations:
// Apply basic 2D transformations (translation, rotation, scaling) to shapes.
// 2. 3D Transformations:
// Extend your program to handle 3D transformations.

// https://learnopengl.com/Getting-started/Transformations

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Callback function for handling framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Vertex Shader with Transformation
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    uniform mat4 transform; // Transformation matrix
    void main() {
        gl_Position = transform * vec4(aPos, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main_task_3_1() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
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

    // Set up viewport and resize callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

    // Vertex data for a triangle
    float vertices_triangle[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    // Vertex Array Object (VAO) and Vertex Buffer Object (VBO) for the triangle
    unsigned int VAO_triangle, VBO_triangle;
    glGenVertexArrays(1, &VAO_triangle);
    glGenBuffers(1, &VBO_triangle);

    // Bind the VAO for the triangle
    glBindVertexArray(VAO_triangle);

    // Bind and set vertex buffer for the triangle
    glBindBuffer(GL_ARRAY_BUFFER, VBO_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);

    // Set the vertex attribute pointers for the triangle
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO for the triangle
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Transformation matrix for translation
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f));

    // Use the shader program for the triangle
    // NOTICE: the example I get from the tutorial does not have this line,
    // but I failed to set the value of the uniform without this line.
    glUseProgram(shaderProgram);

    // Set the transformation matrix in the shader
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(translation));

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program for the triangle
        glUseProgram(shaderProgram);

        // Draw the transformed triangle
        glBindVertexArray(VAO_triangle);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind VAO
        glBindVertexArray(0);

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
