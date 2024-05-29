#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

void DDA(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
    GLfloat dx, dy, steps, xIncrement, yIncrement, x, y;
    dx = x2 - x1;
    dy = y2 - y1;

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
    x = x1;
    y = y1;

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++) {
        glVertex2f(x, y);
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();

    glFlush();
}

int main() {
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

/*
    GLfloat x1,y1,x2,y2;

    cout<<"Enter x-coordinate for first point:";
    cin>>x1;
    cout<<"Enter y-coordinate for first point:";
    cin>>y1;
    cout<<"Enter x-coordinate for second point:";
    cin>>x2;
    cout<<"Enter y-coordinate for second point:";
    cin>>y2;
*/    

    //set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = 1.0f;
    glOrtho(0, 500 * aspectRatio, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        DDA(10,60,420,350);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
