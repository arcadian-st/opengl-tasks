// Task 1: Setting Up the Project
// 1. Initialize a Window:
// Set up a basic window using GLFW.
// Create a main loop that keeps the window open.
// 2. Initialize GLAD:
// Set up GLAD to manage OpenGL function pointers.

// 1. Initialize a Window:
// * GLFW is initialized using `glfwInit()`.
// * A window is created using `glfwCreateWindow()`.
// * The window's OpenGL context is set as the current context with `glfwMakeContextCurrent()`.
// 2. Initialize GLAD:
// * GLAD is initialized with `gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)`.

// https://learnopengl.com/Getting-started/Hello-Window

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main_task_1() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

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

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Enable VSync to limit the frame rate
    glfwSwapInterval(1);

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Rendering commands go here
        // Clear the color buffer with the specified clear color
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}
