# OpenGL Tasks

12 tasks to get started with OpenGL.

This project includes 12 examples to create different basic applications with GLFW and GLAD. 
They are built step-by-step upon the previous example, introducing the fundamental concepts 
of OpenGL to the new learners.

Please note that this project does not include introductions to C++ and GLSL, and it covers 
only a small amount of the most basic concepts of OpenGL. It is better to learn OpenGL systematically 
with lessons or tutorials after you try this examples yourself.

Reference: [learnopengl](https://learnopengl.com/)

## Outlines

1. [Get Started](#get-started)

   1.1 [Environments and Libraries](#environments-and-libraries)

   1.2 [Project Structures](#project-structures)

2. [Tasks Descriptions](#tasks-descriptions)

   2.1 [Task 1: Setting Up the Project](#task-1-setting-up-the-project)

   2.2 [Task 2: Drawing Basic Shapes](#task-2-drawing-basic-shapes)

   2.3 [Task 3: Transformations](#task-3-transformations)

   2.4 [Task 4: Introduction to Shaders](#task-4-introduction-to-shaders)

   2.5 [Task 5: Textures](#task-5-textures)

   2.6 [Task 6: Basic Lighting](#task-6-basic-lighting)

   2.7 [Task 7: Advanced Shaders](#task-7-advanced-shaders)

   2.8 [Task 8: Buffers and Meshes](#task-8-buffers-and-meshes)

   2.9 [Task 9: Camera and User Interaction](#task-9-camera-and-user-interaction)

   2.10 [Task 10: Advanced Topics](#task-10-advanced-topics)

   2.11 [Task 11: Wrapping Up](#task-11-wrapping-up)

   2.12 [Task 12: Final Project - 3D Scene Rendering](#task-12-final-project---3d-scene-rendering)

## Get Started

### Environments and Libraries

  * Microsoft Visual C++ Build Tools v19.28.29915
 
  * CMake v3.27

  * GLWF v3.3.9

  * GLAD with OpenGL v4.6

  * GLM v0.9.9.8

  * Windows 11 system with Intel Core i5 CPU and Nvidia GPU

### Project Structures

  The executable release will be built from the file

  ```
  src/main.cpp
  ```

  and examples for the tasks are placed in the directory

  ```
  src/tasks/
  ```

  Modify the `main.cpp` file above to insert the code for a task like this:

  ```cpp
  #include "./tasks/task1/task_1.cpp"

  int main() {
      return main_task_1();
  }
  ```

  All the executing functions of the tasks have a prefix 'main_' and are easy to find in the codes.

  GLFW, GLAD and GLM supports are placed in the `include` and `lib` folders, and the `src/glad.c` file.

### Build

  All the CMake files except `CMakeLists.txt` are not uploaded in this project.
  You can build and test the project with CMake in the way you like.

  Here is an example to build the project with CMake on the terminal, beginning at the root of the project.

  ```
  mkdir build
  cd build
  cmake ..
  cmake --build .
  cd ..
  ```

  After building the project and returning to the root directory, you can test your executable release in the terminal like this, 
  Assuming that the project was built in the 'Debug' type.

  ```
  ./build/Debug/opengl-tasks
  ```

## Tasks Descriptions

### Task 1: Setting Up the Project

1. Initialize a Window:

   * Set up a basic window using GLFW.
   * Create a main loop that keeps the window open.

1. Initialize GLAD:

   * Set up GLAD to manage OpenGL function pointers.

### Task 2: Drawing Basic Shapes

1. Drawing a Triangle:

   * Create a simple vertex and fragment shader.
   * Render a colored triangle using OpenGL.

1. Drawing a Rectangle:

   * Expand your program to draw a colored rectangle.

1. Drawing Basic Shapes:

   * Experiment with drawing other basic shapes like circles or lines.

### Task 3: Transformations

1. 2D Transformations:

   * Apply basic 2D transformations (translation, rotation, scaling) to shapes.

1. 3D Transformations:

   * Extend your program to handle 3D transformations.

### Task 4: Introduction to Shaders

1. Understanding Shaders:

   * Gain a deeper understanding of vertex and fragment shaders.
   * Experiment with shader variables and uniforms.

1. Color Interpolation:

   * Use shaders to interpolate colors across a shape.

### Task 5: Textures

1. Texture Mapping:

   * Load and apply a simple texture to a shape.

1. Texture Coordinates:

   * Understand and work with texture coordinates.

### Task 6: Basic Lighting

1. Diffuse Lighting:

   * Introduce basic diffuse lighting to your scene.

1. Specular Lighting:

   * Extend your lighting model to include specular highlights.

### Task 7: Advanced Shaders

1. Vertex Shader Effects:

   * Experiment with more advanced effects in the vertex shader.

1. Fragment Shader Effects:

   * Explore complex effects in the fragment shader.

### Task 8: Buffers and Meshes

1. Vertex Buffer Objects (VBOs):

   * Implement and use VBOs for efficient rendering.

1. Index Buffer Objects (IBOs):

   * Learn to use IBOs for indexed rendering.

1.  Rendering a Mesh:

   * Create and render a simple 3D mesh.

### Task 9: Camera and User Interaction

1. Implementing a Camera:

   * Integrate a basic camera system for navigation.

1. User Input Handling:

   * Implement keyboard and mouse input for user interaction.

### Task 10: Advanced Topics

1. Framebuffers:

   * Learn about framebuffers for off-screen rendering.

1. Post-Processing Effects:

   * Implement post-processing effects.

1. Shadow Mapping:

   * Explore shadow mapping techniques.

### Task 11: Wrapping Up

1. Optimizations:

   * Optimize your rendering pipeline for better performance.

1. Documentation and Code Cleanup:

   * Document your code and clean up the project structure.
  
### Task 12: Final Project - 3D Scene Rendering

In this final task, you'll combine the knowledge acquired from the previous tasks to build a 3D scene rendering application.

1. Mesh Loading:

   * Implement a mesh loader to load 3D models (e.g., Wavefront .obj files).
   * Optionally, add support for importing 3D models in glTF or FBX formats to enhance the complexity and visual diversity of your scene.

1. Texture Mapping:

   * Apply textures to the loaded meshes.
   * Experiment with different textures for each mesh.

1. Custom Shaders:

   * Develop custom vertex and fragment shaders.
   * Explore advanced shader techniques, such as normal mapping or specular highlights.

1. Lighting:

   * Implement a lighting system, including ambient, diffuse, and specular lighting.
   * Experiment with multiple light sources.

1. Camera Controls:

   * Implement a camera system with the ability to orbit, pan, and zoom.
   * Allow user interaction to navigate the 3D scene.

1. User Interface (Optional):

   * Integrate a simple user interface (UI) to control aspects of the rendering, such as lighting parameters or shader effects.

1. Scriptable Behaviors (Optional):

   * Develop a scripting system to attach custom behaviors to objects in the scene.
   * Allow users to script animations or interactions.

1. Optimizations:

   * Optimize the rendering pipeline for better performance.
   * Explore techniques such as frustum culling or level of detail (LOD).

1. Documentation and Code Cleanup:

   * Document your code thoroughly.
   * Clean up the project structure and ensure it is well-organized.

1. Demonstration:

   * Create a showcase scene that demonstrates the capabilities of your 3D rendering application.
   * Capture screenshots or record a video to showcase your project.
