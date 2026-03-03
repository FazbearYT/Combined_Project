#include "WaveSurfaceModule.h"
#include <GL/freeglut.h>
#include <cmath>
#include <sstream>

void WaveSurfaceModule::init() {
    gTime = 0.0f;
    gSpeed = 1.0f;
    gAmp = 1.0f;
    gRot = 0.0f;
    gPause = false;
    winWidth = 800;
    winHeight = 600;
}

float WaveSurfaceModule::func(float x, float y) {
    return gAmp * std::sin(x + gTime) * std::cos(y - gTime);
}

void WaveSurfaceModule::project(float x, float y, float z, float& sx, float& sy) {
    float c = std::cos(gRot);
    float s = std::sin(gRot);
    float xr = x * c - y * s;
    float yr = x * s + y * c;

    float isoX = xr - yr;
    float isoY = (xr + yr) * 0.5f - z;
    float scale = 20.0f;

    sx = winWidth / 2.0f + isoX * scale;
    sy = winHeight / 2.0f + isoY * scale;
}

void WaveSurfaceModule::update(float dt) {
    if (!gPause) {
        gTime += 0.02f * gSpeed * dt * 60.0f;
    }
}

void WaveSurfaceModule::render() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const int NX = 30;
    const int NY = 30;
    const float XMIN = -5.0f;
    const float XMAX = 5.0f;
    const float YMIN = -5.0f;
    const float YMAX = 5.0f;

    float dx = (XMAX - XMIN) / (NX - 1);
    float dy = (YMAX - YMIN) / (NY - 1);
    float sx, sy;

    // Сетка по X (синие линии)
    glColor3f(0.0f, 0.0f, 1.0f);
    for (int i = 0; i < NX; ++i) {
        float x = XMIN + i * dx;
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < NY; ++j) {
            float y = YMIN + j * dy;
            float z = func(x, y);
            project(x, y, z, sx, sy);
            glVertex2f(sx, sy);
        }
        glEnd();
    }

    // Сетка по Y (красные линии)
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int j = 0; j < NY; ++j) {
        float y = YMIN + j * dy;
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < NX; ++i) {
            float x = XMIN + i * dx;
            float z = func(x, y);
            project(x, y, z, sx, sy);
            glVertex2f(sx, sy);
        }
        glEnd();
    }

    // Информация
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(10, 20);

    std::ostringstream oss;
    oss << "Time: " << gTime << " Amp: " << gAmp << " Speed: " << gSpeed;
    std::string info = oss.str();

    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glRasterPos2f(10, winHeight - 40);
    std::string controls = "W/S: speed, +/-: amp, A/D: rotate, SPACE: pause, R: reset";
    for (char c : controls) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void WaveSurfaceModule::handleInput(unsigned char key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
    case ' ':
        gPause = !gPause;
        break;
    case 'w':
    case 'W':
        gSpeed *= 1.1f;
        break;
    case 's':
    case 'S':
        gSpeed /= 1.1f;
        break;
    case '+':
    case '=':
        gAmp *= 1.1f;
        break;
    case '-':
        gAmp /= 1.1f;
        break;
    case 'a':
    case 'A':
        gRot -= 0.08f;
        break;
    case 'd':
    case 'D':
        gRot += 0.08f;
        break;
    case 'r':
    case 'R':
        init();
        break;
    }
}

void WaveSurfaceModule::handleSpecialInput(int key, int x, int y) {
    (void)key; (void)x; (void)y;
}