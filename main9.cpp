#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;
void transform(int x1, int y1, int x2, int y2, int x3, int y3, float transform[][3])
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0, 600);
    glVertex2f(0, -600);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(600, 0);
    glVertex2f(-600, 0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
    int tri[3][3]{
        {x1, x2, x3},
        {y1, y2, y3},
        {1, 1, 1}};
    int trans_tri[3][3];
    int i, j, k;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            trans_tri[i][j] = 0;
        }
    }
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            for (k = 0; k < 3; ++k)
            {
                trans_tri[i][j] += transform[i][k] * tri[k][j];
            }
        }
    }
    glBegin(GL_POLYGON);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 1);
    glVertex2f(trans_tri[0][0], trans_tri[1][0]);
    glVertex2f(trans_tri[0][1], trans_tri[1][1]);
    glVertex2f(trans_tri[0][2], trans_tri[1][2]);
    glEnd();
}
int main()
{
    GLFWwindow *window;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    window = glfwCreateWindow(1000, 1000, "TRASNFORMATION", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width > height)
    {
        float aspect = static_cast<float>(width) / static_cast<float>(height);
        glOrtho(-600 * aspect, 600 * aspect, -600, 600, -1, 1);
    }
    else
    {
        float aspect = static_cast<float>(height) / static_cast<float>(width);
        glOrtho(-600, 600, -600 * aspect, 600 * aspect, -1, 1);
    }
    glMatrixMode(GL_MODELVIEW);
    float tx, ty;
     tx=55;
    ty = 100;
    float translate[3][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};
    while (!glfwWindowShouldClose(window))
    {
        transform(5, 5, 150, 50, 145, 170, translate);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
