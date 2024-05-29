#include <iostream>
#include <GLFW/glfw3.h>
#include<cmath>
using namespace std;

void DDA(GLfloat d,GLfloat e,GLfloat f,GLfloat c, float r, float b, float g) {
    glColor3d(r,b,g);
    GLfloat dx, dy, steps, xIncrement, yIncrement, x, y;
    dx = f - d;
    dy = c - e;

    if (fabs(dx) > fabs(dy))
    {
        steps = fabs(dx);
    }
    else
    {
        steps = fabs(dy);
    }

    xIncrement = dx / steps;
    yIncrement = dy / steps;
    x = d;
    y = e;

    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++) {
        glVertex2f(x, y);
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();

    glFlush();
}

// Function to draw histogram
void drawhistogram(GLfloat frequencies[], GLfloat size) {    
    glClear(GL_COLOR_BUFFER_BIT);
    float r,b,g ;
        r = 0.15f;
        b = 0.15f;
        g = 0.15f;
    for (int i = 0; i < size; ++i) {
        DDA(i*50,0,i*50,frequencies[i],r,b,g);
        DDA(i*50,frequencies[i],(i+1)*50, frequencies[i],r,b,g);
        DDA((i+1)*50, frequencies[i],(i+1)*50, 0,r,b,g);
        r=r+0.15f;
        b=b+0.15f;
        g=g+0.15f;
    }
    glFlush();
}

int main() {
    GLfloat frequencies[5] = {200 , 300, 400,100, 500};

    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(500, 500, "DDA Line Drawing Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 500, 500);

    //set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = 1.0f;
    glOrtho(0, 500*aspectRatio, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        drawhistogram(frequencies, 5);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
