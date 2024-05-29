#include <GLFW/glfw3.h>
#include <cmath>

void drawKU(float x, float y, float radius) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(7.0);
    glBegin(GL_LINES);
    glVertex2f(x - radius / 4 + 0.03, y + radius / 4);
    glVertex2f(x - radius / 4 + 0.03, y - radius / 4);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((x - radius / 4 + 0.03) +0.01, y);
    glVertex2f(x + 0.03, y + radius / 4);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((x - radius / 4 + 0.03) +0.01, y + 0.01);
    glVertex2f(x + 0.03, y - radius / 4);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x + 0.029, (y - radius / 4)+0.007);
    glVertex2f((x + radius / 4) + 0.02 , y+0.007);
    glEnd();
}

void drawCircle(float x, float y, float radius, float red, float green, float blue) {
    int numSegments = 500;
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawTriangle(float x, float y, float radius) {
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(15.0);
    glBegin(GL_LINES);
    glVertex2f(x - radius, y - 0.1);
    glVertex2f(x + radius, y - 0.1);
    glVertex2f(x + radius, y - 0.11);
    glVertex2f(x, y + 2 * radius - 0.11);
    glVertex2f(x, y + 2 * radius - 0.11);
    glVertex2f(x - radius, y - 0.11 );
    glEnd();
    drawCircle(x - radius, y - 0.1, 0.04, 1.0, 1.0, 1.0);
    drawCircle(x + radius, y - 0.1, 0.04, 1.0, 1.0, 1.0);
    drawCircle(x, y + 2 * radius - 0.11, 0.04, 1.0, 1.0, 1.0);
}

void drawrevTriangle(float x, float y, float radius) {
    glColor3f(0.9921, 0.6823, 0.6745);
    glLineWidth(4.0);
    glBegin(GL_POLYGON);
    glVertex2f(x - radius, y - 0.15 );
    glVertex2f(x + radius, y - 0.15);
    glVertex2f(x, y + 2 * radius - 0.15);
    glEnd();
}

void drawFlag(float l, float b)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(l/2, b/2);
    glVertex2f(l/2, -b/2);
    glVertex2f(-l/2, -b/2);
    glVertex2f(-l/2, b/2);
    glEnd();
}

void display(GLFWwindow* window) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    drawFlag(1.0, 0.8);
    drawCircle(0.0, 0.0, 0.28, 1.0, 0.0, 0.0);
    drawCircle(0.0, 0.0, 0.25, 0.6627, 0.7764, 0.8941);
    drawCircle(0.0, 0.0, 0.182, 0.9568, 0.9137, 0.4431);
    drawrevTriangle(0.0, 0.260, -0.15);
    drawTriangle(0.0, 0.0, 0.15);
    drawKU(-0.015, 0.0, 0.182);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(900, 900, "KU LOGO", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) 
    {
        display(window);
    }

    glfwTerminate();
    return 0;
}
