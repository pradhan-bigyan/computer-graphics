#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;
void ellp_MDA(GLfloat x1,GLfloat y1,GLfloat rx,GLfloat ry) {
   glBegin(GL_POINTS);
   GLfloat x,y,p10,p1k,p20,p2k;
   x = 0;
   y = ry;
   glVertex2f(x+x1, y+y1);
   glVertex2f( -x+x1, y+y1);
   glVertex2f( x+x1,  -y+y1);
   glVertex2f( -x+x1,  -y+y1);
   p10 = ry*ry - rx*rx*ry + (1/4)*rx*rx;
   p1k = p10;
   while(2*ry*ry*x < 2*rx*rx*y)
   {
       if(p1k<0)
       {
           x = x + 1;
           y = y + 0;
           p1k = p1k + 2*ry*ry*x + ry*ry;
       }
       else
       {
           x = x + 1;
           y = y - 1;
           p1k = p1k + 2*ry*ry*x - 2*rx*rx*y + ry*ry;
       }
       glVertex2f( x+x1,  y+y1);
       glVertex2f( -x+x1, y+y1);
       glVertex2f( x+x1,  -y+y1);
       glVertex2f( -x+x1,  -y+y1);
   }
   p20 = ry*ry*(x + 1/2)*(x + 1/2) + rx*rx*(y-1)*(y-1) - rx*rx*ry*ry ;
   p2k = p20;
   while(y != 0)
   {
       if(p2k<=0)
       {
           x = x + 1;
           y = y - 1;
           p2k = p2k + 2*ry*ry*x - 2*rx*rx*y + rx*rx;
       }
       else
       {
           x = x + 0;
           y = y - 1;
           p2k = p2k - 2*rx*rx*y + rx*rx;
       }
       glVertex2f( x+x1,  y+y1);
       glVertex2f( -x+x1, y+y1);
       glVertex2f( x+x1,  -y+y1);
       glVertex2f( -x+x1,  -y+y1);
   }
   glEnd();
}
int main() {
   GLFWwindow* window;
   if (!glfwInit()) {
       std::cerr << "Failed to initialize GLFW" << std::endl;
       return -1;
   }
   window = glfwCreateWindow(1200, 1200, "Ellipse Drawing Algorithm", NULL, NULL);
   if (!window) {
       glfwTerminate();
       return -1;
   }
   glfwMakeContextCurrent(window);
   int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width > height) {
        float aspect = static_cast<float>(width) / static_cast<float>(height);
        glOrtho(-600 * aspect, 600 * aspect, -600, 600, -1, 1);
    } 
    else {
        float aspect = static_cast<float>(height) / static_cast<float>(width);
        glOrtho(-600, 600, -600 * aspect, 600 * aspect, -1, 1);
    }
   glMatrixMode(GL_MODELVIEW);
   // Loop until the user closes the window
   while (!glfwWindowShouldClose(window)) {
       ellp_MDA(0, 0, 400, 300);
       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   // Terminate GLFW
   glfwTerminate();
   return 0;
}