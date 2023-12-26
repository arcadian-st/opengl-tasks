// This is a modified version of task_1.cpp
// with a maximum frame rate of 60 fps.

// The result frame rate may be lower than 60 fps
// due to the accuracy of the sleep mechanism or other reasons.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <chrono>
#include <thread>

// Callback function for handling framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

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

    // Set up viewport and resize callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Disnable VSync
    glfwSwapInterval(0);

    // Variables for FPS calculation
    int frameCount = 0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::high_resolution_clock::now();

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {

        // Rendering commands go here
        // Clear the color buffer with the specified clear color
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Calculate FPS
        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count();

        if (elapsedTime >= 1) {
            double fps = frameCount / static_cast<double>(elapsedTime);
            std::cout << "FPS: " << fps << std::endl;

            // Reset variables
            frameCount = 0;
            lastTime = currentTime;
        }

        // Calculate the time to wait for the next frame
        double frameTime = 1.0 / 60.0;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        double sleepTime = frameTime - duration.count() * 1e-6;

        if (sleepTime > 0.0) {
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
        }

        start = std::chrono::high_resolution_clock::now();
    }

    // Cleanup
    glfwTerminate();
    return 0;
}
