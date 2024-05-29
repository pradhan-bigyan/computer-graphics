#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;

void draw_polygon(float x[][2], float y[][2], float r, float g, float b);

void create_window(GLFWwindow* window) {
    int wx1, wy1, wx2, wy2;
    wx1 = 200; wy1 = 300; wx2 = 700; wy2 = 750;
    float p,q,r;

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping window
    glBegin(GL_LINE_LOOP);
    glColor3d(1, 1, 1);
    glVertex2f(wx1, wy1);
    glVertex2f(wx2, wy1);
    glVertex2f(wx2, wy2);
    glVertex2f(wx1, wy2);
    glEnd();

    // Polygon to be clipped
    float px[5][2] = {
        {100, 400},
        {400, 900},
        {900, 450},
        {450, 350},
        {350, 100}};
    float py[5][2] = {
        {500, 250},
        {250, 500},
        {500, 950},
        {950, 550},
        {550, 500}};
    
    draw_polygon(px, py, 1,0,0);

    float delx[5];
    float dely[5];
    for(int i=0; i<5; i++)
    {
        delx[i] = px[i][1]-px[i][0];
        dely[i] = py[i][1]-py[i][0];
    }
//for left clipping
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(px[i][j] < wx1)
            {
                p = -delx[i]; q = px[i][j] - wx1;
                r = q/p;
                px[i][j] = px[i][j] + r * delx[i];
                py[i][j] = py[i][j] + r * dely[i];
            }
        }
    }
//for bottom clipping
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(py[i][j] < wy1)
            {
                p = -dely[i]; q = py[i][j] - wy1;
                r = q/p;
                px[i][j] = px[i][j] + r * delx[i];
                py[i][j] = py[i][j] + r * dely[i];
            }
        }
    }
//for right clipping
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(px[i][j] > wx2)
            {
                p = delx[i]; q = wx2 - px[i][j];
                r = q/p;
                px[i][j] = px[i][j] + r * delx[i];
                py[i][j] = py[i][j] + r * dely[i];
            }
        }
    }
//for top clipping
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<2; j++)
        {
            if(py[i][j] > wy2)
            {
                p = dely[i]; q = wy2 - py[i][j];
                r = q/p;
                px[i][j] = px[i][j] + r * delx[i];
                py[i][j] = py[i][j] + r * dely[i];
            }
        }
    }

    draw_polygon(px, py, 0,1,0);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void draw_polygon(float x[][2], float y[][2], float r, float g, float b)
{
    glColor3f(r,g,b);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<2; j++)
        {
            glVertex2f(x[i][j], y[i][j]);
        }
    }
    glEnd();
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1000, 1000, "Cohen Sutherland Polygon Clipping Algorithm", NULL, NULL);
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
