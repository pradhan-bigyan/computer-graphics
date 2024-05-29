#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

void circ_PC(GLfloat x1,GLfloat y1,GLfloat r) {
    glBegin(GL_POINTS);
    GLfloat x,y,deltheta,theta,n;
    n = 800;
    deltheta = 2*M_PI/n ;
    theta = 0;
    while(theta < (M_PI/4))
    {
        x = r * cosf(theta);
        y = r * sinf(theta);
        glVertex2f( x+x1,  y+y1);
        glVertex2f( -x+x1, y+y1);
        glVertex2f( x+x1,  -y+y1);
        glVertex2f( -x+x1,  -y+y1);
        glVertex2f( y+y1, x+x1);
        glVertex2f( -y+y1, x+x1);
        glVertex2f( y+y1, -x+x1);
        glVertex2f( -y+y1, -x+x1);
        theta = theta + deltheta;
    }

    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Circle Drawing Algorithm(Polar)", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 1000, 1000);

    //set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-500, 500, -500, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        circ_PC(0, 0, 200);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
