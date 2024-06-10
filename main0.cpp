#include <cmath>
#include <GL/glu.h>
#include <GLUT/glut.h>

// Constants for planet positions and sizes
const float sunRadius = 1.0f;
const float planetRadii[8] = {0.3f, 0.5f, 0.6f, 0.4f, 0.7f, 0.5f, 0.6f, 0.4f};
const float planetDistances[8] = {2.0f, 3.5f, 5.0f, 6.5f, 8.0f, 9.5f, 11.0f, 12.5f};
const float planetSpeeds[8] = {1.0f, 0.8f, 0.6f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f};

// Function to draw a sphere using GLUT
void drawSphere(float radius) {
    glutSolidSphere(radius, 50, 50);
}

// Function to draw an orbit
void drawOrbit(float radius) {
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 100; i++) {
        float angle = 2.0f * M_PI * i / 100;
        glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
    }
    glEnd();
}

// Function to initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Function to render the scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the Sun
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glTranslatef(0.0f, 0.0f, 0.0f); // Sun at the center
    drawSphere(sunRadius);
    glPopMatrix();

    // Draw the planets and their orbits
    float planetColors[][3] = {
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.5f, 0.0f, 0.5f}, // Purple
        {0.5f, 0.5f, 0.5f}, // Gray
        {0.5f, 0.5f, 0.0f}, // Olive
        {0.0f, 1.0f, 1.0f}  // Cyan
    };

    for (int i = 0; i < 8; ++i) {
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f); // Orbit color
        drawOrbit(planetDistances[i]);

        glColor3f(planetColors[i][0], planetColors[i][1], planetColors[i][2]);
        float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0f * planetSpeeds[i];
        float x = planetDistances[i] * cos(angle);
        float z = planetDistances[i] * sin(angle);
        glTranslatef(x, 0.0f, z);
        drawSphere(planetRadii[i]);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 1.0, 100.0);

    // Set the camera to look from the top down
    gluLookAt(0.0, 30.0, 0.0, // Eye position
              0.0, 0.0, 0.0,  // Look-at point
              0.0, 0.0, -1.0);// Up direction
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solar System");

    initOpenGL();

    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutIdleFunc(renderScene);

    glutMainLoop();
    return 0;
}