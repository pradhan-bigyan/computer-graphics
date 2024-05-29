#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    if (!mode) {
        std::cerr << "Failed to get video mode" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "Screen Resolution: " << mode->width << "x" << mode->height << std::endl;

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
