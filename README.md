# OpenGL Tasks

12 tasks to get started with OpenGL.

This project includes 12 examples to create different basic applications with GLFW and GLAD. 
They are built step-by-step upon the previous example, introducing the fundamental concepts 
of OpenGL to the new learners.

Please note that this project does not include introductions to C++ and GLSL, and it covers 
only a small amount of the most basic concepts of OpenGL. It is better to learn OpenGL systematically 
with lessons or tutorials after you try this examples yourself.

## Outlines

## Get Started

### Environments

  * Microsoft Visual C++ Build Tools v19.28.29915
 
  * CMake v3.27

  * GLWF v3.3.9

  * GLAD with OpenGL v4.6

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
  #include "./tasks/task1.cpp"

  int main() {
      return main_task1();
  }
  ```

  All the executing functions of the tasks have a prefix 'main_' and are easy to find in the codes.

  GLFW and GLAD supports are placed in the `include` and `lib` folders, and the `src/glad.c` file.

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

