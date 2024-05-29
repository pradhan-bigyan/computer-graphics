#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <algorithm>
using namespace std;

void lineclipping(int wx1, int wy1, int wx2, int wy2, int l1x1, int l1y1, int l1x2, int l1y2);

void create_window(GLFWwindow* window) {
    int wx1, wy1, wx2, wy2;
    wx1 = 200; wy1 = 300; wx2 = 700; wy2 = 750;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 1, 1);

    // Draw the clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(wx1, wy1);
    glVertex2f(wx2, wy1);
    glVertex2f(wx2, wy2);
    glVertex2f(wx1, wy2);
    glEnd();

    // Line to be clipped
    int l1x1 = 100, l1y1 = 100, l1x2 = 800, l1y2 = 100;
    int l2x1 = 250, l2y1 = 650, l2x2 = 600, l2y2 = 350;
    int l3x1 = 300, l3y1 = 100, l3x2 = 500, l3y2 = 900;
    lineclipping(wx1, wy1, wx2, wy2, l1x1, l1y1, l1x2, l1y2);
    lineclipping(wx1, wy1, wx2, wy2, l2x1, l2y1, l2x2, l2y2);
    lineclipping(wx1, wy1, wx2, wy2, l3x1, l3y1, l3x2, l3y2);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void lineclipping(int wx1, int wy1, int wx2, int wy2, int l1x1, int l1y1, int l1x2, int l1y2) {
    float delx = l1x2 - l1x1;
    float dely = l1y2 - l1y1;
    
    float u1 = 0.0, u2 = 1.0;
    float p[4], q[4];
    
    p[0] = -delx; q[0] = l1x1 - wx1;
    p[1] = delx;  q[1] = wx2 - l1x1;
    p[2] = -dely; q[2] = l1y1 - wy1;
    p[3] = dely;  q[3] = wy2 - l1y1;
    
    bool should_clip = true;
    
    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            should_clip = false;
            break;
        }
        if (p[i] != 0) {
            float r = q[i] / p[i];
            if (p[i] < 0) {
                u1 = max(u1, r);
            } else {
                u2 = min(u2, r);
            }
        }
    }

    if (u1 > u2 || !should_clip) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(l1x1, l1y1);
        glVertex2f(l1x2, l1y2);
        glEnd();
    } else {
        float new_x1 = l1x1 + u1 * delx;
        float new_y1 = l1y1 + u1 * dely;
        float new_x2 = l1x1 + u2 * delx;
        float new_y2 = l1y1 + u2 * dely;

        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(new_x1, new_y1);
        glVertex2f(new_x2, new_y2);
        glEnd();

        glColor3f(1, 0, 0);
        if (u1 > 0) {
            glBegin(GL_LINES);
            glVertex2f(l1x1, l1y1);
            glVertex2f(new_x1, new_y1);
            glEnd();
        }
        if (u2 < 1) {
            glBegin(GL_LINES);
            glVertex2f(new_x2, new_y2);
            glVertex2f(l1x2, l1y2);
            glEnd();
        }
    }
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Liang-Barsky Line Clipping Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 1000, 1000);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1000, 0, 1000, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        create_window(window);
    }

    glfwTerminate();
    return 0;
}
