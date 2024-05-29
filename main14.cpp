#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
using namespace std;
void multiply(float m1[][3], float m2[][3], float r[][3])
{
    int i, j, k;
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            for (k = 0; k < 3; ++k)
            {
                r[i][j] += m1[i][k] * m2[k][j];
            }
        
    }
}
}
void transform(float x1, float y1, float x2, float y2, float x3, float y3, float translate[][3], float ntranslate[][3], float rotate[][3], float nrotate[][3], float scale[][3])
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
    float tri[3][3] = {
        {x1, x2, x3},
        {y1, y2, y3},
        {1, 1, 1}} ;
    float trans1[3][3];
    float rot1[3][3];
    float scale1[3][3];
    float rot2[3][3];
    float trans2[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            trans1[i][j] = 0;
            trans2[i][j] = 0;
            rot1[i][j] = 0;
            rot2[i][j] = 0;
            scale1[i][j] = 0;
        }
    }
    multiply(ntranslate, tri, trans1);
    multiply(nrotate, trans1, rot1);
    multiply(scale, rot1, scale1);
    multiply(rotate, scale1, rot2);
    multiply(translate, rot2, trans2);
    glBegin(GL_POLYGON);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glVertex2f(trans2[0][0], trans2[1][0]);
    glVertex2f(trans2[0][1], trans2[1][1]);
    glVertex2f(trans2[0][2], trans2[1][2]);
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
    float sy, sx;
    float theta = 60;
    sx = 2;
    sy = 2;
    float translate[3][3] = {{1, 0, 0}, {0, 1, 5}, {0, 0, 1}};
    float ntranslate[3][3] = {{1, 0, 0}, {0, 1, -5}, {0, 0, 1}};
    theta = theta * 3.14159 / 180;
    float rotate[3][3] = {{cosf(theta), -sinf(theta), 0}, {sinf(theta), cosf(theta), 0}, {0, 0, 1}};
    float nrotate[3][3] = {{cosf(-theta), -sinf(-theta), 0}, {sinf(-theta), cosf(-theta), 0}, {0, 0, 1}};
    float scale[3][3] = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
    while (!glfwWindowShouldClose(window))
    {
        transform(5, 5, 150, 50, 145, 170, translate, ntranslate, rotate, nrotate, scale);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
