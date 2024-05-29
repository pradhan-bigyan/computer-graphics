#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

void para_MDA(GLfloat x1,GLfloat y1,GLfloat fc) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    GLfloat x, y, p10, p1k, p20, p2k;
    x = 0;
    y = 0;
    p10 = 1 - 2 * fc;
    p1k = p10;
    while (y < (2 * fc)) {
        if (p1k < 0) {
            x = x + 0;
            y = y + 1;
            p1k = p1k + 2 * y + 1;
        } else {
            x = x + 1;
            y = y + 1;
            p1k = p1k + 2 * y + 1 - 4 * fc;
        }
        glVertex2f(x, y);
        glVertex2f(x, -y);
    }

    p20 = (y + 1 / 2) * (y + 1 / 2) - 4 * fc * (x + 1);
    p2k = p20;

    while (x < x1 || y < y1) {
        if (p2k < 0) {
            x = x + 1;
            y = y + 1;
            p2k = p2k + 2 * y - 4 * fc;

        } else {
            x = x + 1;
            y = y + 0;
            p2k = p2k - 4 * fc;
        }

        glVertex2f(x, y);
        glVertex2f(x, -y);
    }

    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Parabola Drawing Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 1000, 1000);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    
    while (!glfwWindowShouldClose(window)) {
        para_MDA(350, 700, 50);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
