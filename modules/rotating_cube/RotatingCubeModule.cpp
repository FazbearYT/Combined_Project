#include "RotatingCubeModule.h"
#include <GL/freeglut.h>
#include <sstream>

void RotatingCubeModule::init() {
    angleX = 0.0f;
    angleY = 0.0f;
    autoRotate = 1;
    wireframeMode = 0;
}

void RotatingCubeModule::drawCube() {
    if (wireframeMode == 1) {
        glColor3ub(255, 255, 255);
        glBegin(GL_LINES);
        glVertex3f(-1, -1, 1); glVertex3f(1, -1, 1);
        glVertex3f(1, -1, 1); glVertex3f(1, 1, 1);
        glVertex3f(1, 1, 1); glVertex3f(-1, 1, 1);
        glVertex3f(-1, 1, 1); glVertex3f(-1, -1, 1);
        glVertex3f(-1, -1, -1); glVertex3f(1, -1, -1);
        glVertex3f(1, -1, -1); glVertex3f(1, 1, -1);
        glVertex3f(1, 1, -1); glVertex3f(-1, 1, -1);
        glVertex3f(-1, 1, -1); glVertex3f(-1, -1, -1);
        glVertex3f(-1, -1, 1); glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, 1); glVertex3f(1, -1, -1);
        glVertex3f(1, 1, 1); glVertex3f(1, 1, -1);
        glVertex3f(-1, 1, 1); glVertex3f(-1, 1, -1);
        glEnd();
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(-1, 1, 1);
        glEnd();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, -1);
        glVertex3f(-1, 1, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(1, -1, -1);
        glEnd();

        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1, 1, -1);
        glVertex3f(-1, 1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, -1);
        glEnd();

        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);
        glVertex3f(-1, -1, 1);
        glEnd();

        glColor3f(1.0f, 0.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex3f(1, -1, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, -1, 1);
        glEnd();

        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex3f(-1, -1, -1);
        glVertex3f(-1, -1, 1);
        glVertex3f(-1, 1, 1);
        glVertex3f(-1, 1, -1);
        glEnd();
    }
}

void RotatingCubeModule::update(float dt) {
    if (autoRotate) {
        angleY += 0.5f * dt * 60.0f;
        if (angleY >= 360.0f) angleY -= 360.0f;
    }
}

void RotatingCubeModule::render() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    if (wireframeMode == 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    drawCube();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, 20);

    std::string controls = "Arrows: rotate, A: auto, S: toggle mode, R: reset";
    for (char c : controls) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void RotatingCubeModule::handleInput(unsigned char key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
    case 'r':
    case 'R':
        angleX = 0.0f;
        angleY = 0.0f;
        autoRotate = 0;
        break;
    case 'a':
    case 'A':
        autoRotate = !autoRotate;
        break;
    case 's':
    case 'S':
        wireframeMode = 1 - wireframeMode;
        break;
    case 'w':
    case 'W':
        wireframeMode = 1;
        break;
    case 'f':
    case 'F':
        wireframeMode = 0;
        break;
    }
}

void RotatingCubeModule::handleSpecialInput(int key, int x, int y) {
    autoRotate = 0;
    const float step = 5.0f;
    switch (key) {
    case GLUT_KEY_UP:
        angleX -= step;
        break;
    case GLUT_KEY_DOWN:
        angleX += step;
        break;
    case GLUT_KEY_LEFT:
        angleY -= step;
        break;
    case GLUT_KEY_RIGHT:
        angleY += step;
        break;
    }
}