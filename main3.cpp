#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;

void BLDA(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2) {
    GLfloat M,p,dx,dy,x,y,t;
    glClear(GL_COLOR_BUFFER_BIT);

    if((x2-x1)==0)
       M = (y2-y1);
    else
        M = (y2-y1)/(x2-x1);

    if(fabs(M)<1)
    {
        if(x1>x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2-x1);
        dy = fabs(y2-y1);

        p = 2*dy-dx;

        x=x1;
        y=y1;

        glBegin(GL_POINTS);
            while(x<=x2)
            {
              glVertex2f(x,y);
              x=x+1;

              if(p>=0)
              {
                 if(M<1)
                    y=y+1;
                else
                    y=y-1;
                 p = p+2*dy-2*dx;
              }
              else
              {
                  p = p+2*dy;
              }
            }
        glEnd();
    }

    if(fabs(M)>=1)
    {
        if(y1>y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2-x1);
        dy = fabs(y2-y1);

        p = 2*dx-dy;

        x=x1;
        y=y1;

        glBegin(GL_POINTS);
            while(y<=y2)
            {
              glVertex2f(x,y);
              y=y+1;

              if(p>=0)
              {
                 if(M>=1)
                    x=x+1;
                else
                    x=x-1;
                 p = p+2*dx-2*dy;
              }
              else
              {
                  p = p+2*dx;
              }
            }
        glEnd();
    }

    glFlush();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(500, 500, "BLA Line Drawing Algorithm", NULL, NULL);
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
    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        BLDA(21,100,350, 475);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
