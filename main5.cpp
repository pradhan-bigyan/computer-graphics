#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

void circ_MDA(GLfloat x1,GLfloat y1,GLfloat r) {
    glBegin(GL_POINTS);
    GLfloat x,y,p0,pk;
    x = 0;
    y = r;
    glVertex2f(x+x1, y+y1);
    glVertex2f( -x+x1, y+y1);
    glVertex2f( x+x1,  -y+y1);
    glVertex2f( -x+x1,  -y+y1);
    glVertex2f( y+y1, x+x1);
    glVertex2f( -y+y1, x+x1);
    glVertex2f( y+y1, -x+x1);
    glVertex2f( -y+y1, -x+x1);
    p0 = 5/4 - r;
    pk = p0;
    while(x < y)
    {
        if(pk<0)
        {
            x = x + 1;
            y = y + 0;
            pk = pk + 2*x + 1;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            pk = pk + 2*x + 1 - 2*y;
        }
        glVertex2f( x+x1,  y+y1);
        glVertex2f( -x+x1, y+y1);
        glVertex2f( x+x1,  -y+y1);
        glVertex2f( -x+x1,  -y+y1);
        glVertex2f( y+y1, x+x1);
        glVertex2f( -y+y1, x+x1);
        glVertex2f( y+y1, -x+x1);
        glVertex2f( -y+y1, -x+x1);
    }

    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Circle Drawing Algorithm", NULL, NULL);
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
        circ_MDA(0, 0, 200);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
