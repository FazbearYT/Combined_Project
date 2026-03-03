#include "PendulumModule.h"
#include <GL/freeglut.h>
#include <cmath>
#include <sstream>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void PendulumModule::init() {
    positionR = REST_LENGTH + 70.0f;
    angle = 0.5f;
    velocityR = 0.0f;
    angularVelocity = 0.0f;
    isRunning = true;
    trajectory.clear();

    float initialX = positionR * sin(angle);
    float initialY = -positionR * cos(angle);
    trajectory.push_back({ pivotX + initialX, pivotY - initialY });

    std::cout << "PendulumModule initialized! positionR=" << positionR << std::endl;
}

void PendulumModule::update(float dt) {
    if (!isRunning) return;

    float x = positionR * sin(angle);
    float y = -positionR * cos(angle);
    trajectory.push_back({ pivotX + x, pivotY - y });

    if (static_cast<int>(trajectory.size()) > MAX_TRAJECTORY_POINTS) {
        trajectory.erase(trajectory.begin());
    }

    // Расчет сил
    float springForce = -SPRING_CONSTANT * (positionR - REST_LENGTH);
    float gravityTangential = -MASS * GRAVITY * sin(angle);
    float gravityRadial = MASS * GRAVITY * cos(angle);

    // Ускорения
    float radialAcceleration = (springForce + gravityRadial) / MASS -
        positionR * angularVelocity * angularVelocity;
    float angularAcceleration = (gravityTangential - 2 * velocityR * angularVelocity) / positionR;

    // Обновление скоростей и позиций
    velocityR += radialAcceleration * dt;
    angularVelocity += angularAcceleration * dt;

    positionR += velocityR * dt;
    angle += angularVelocity * dt;

    // Затухание
    velocityR *= 0.999f;
    angularVelocity *= 0.99f;

    if (positionR < REST_LENGTH * 0.1f) {
        positionR = REST_LENGTH * 0.1f;
        velocityR = 0.0f;
    }
}

void PendulumModule::render() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Сетка
    glColor3fv(GRID_COLOR);
    const int gridStep = 50;
    for (int x = 0; x <= static_cast<int>(WINDOW_WIDTH); x += gridStep) {
        glBegin(GL_LINES);
        glVertex2f(static_cast<float>(x), 0.0f);
        glVertex2f(static_cast<float>(x), WINDOW_HEIGHT);
        glEnd();
    }
    for (int y = 0; y <= static_cast<int>(WINDOW_HEIGHT); y += gridStep) {
        glBegin(GL_LINES);
        glVertex2f(0.0f, static_cast<float>(y));
        glVertex2f(WINDOW_WIDTH, static_cast<float>(y));
        glEnd();
    }

    // Оси
    glColor3fv(AXIS_COLOR);
    glBegin(GL_LINES);
    glVertex2f(0.0f, WINDOW_HEIGHT / 2.0f);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2.0f);
    glVertex2f(WINDOW_WIDTH / 2.0f, 0.0f);
    glVertex2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT);
    glEnd();

    // Траектория
    glColor3fv(TRAJECTORY_COLOR);
    glBegin(GL_LINE_STRIP);
    for (const auto& point : trajectory) {
        glVertex2f(point.first, point.second);
    }
    glEnd();

    // Позиция груза
    float massX = positionR * sin(angle);
    float massY = -positionR * cos(angle);
    float massScreenX = pivotX + massX;
    float massScreenY = pivotY - massY;

    // Пружина
    glColor3fv(SPRING_COLOR);
    drawSpring(pivotX, pivotY, massScreenX, massScreenY, 10);

    // Точка подвеса
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2f(pivotX, pivotY);
    glEnd();

    // Груз
    glColor3fv(MASS_COLOR);
    glPointSize(20.0f);
    glBegin(GL_POINTS);
    glVertex2f(massScreenX, massScreenY);
    glEnd();

    // Вектор направления
    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(massScreenX, massScreenY);
    glVertex2f(massScreenX + 15.0f * sin(angle), massScreenY - 15.0f * cos(angle));
    glEnd();

    // Информация
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(20, 20);

    std::ostringstream oss;
    oss << "Spring length: " << positionR
        << " Angle: " << (angle * 180 / M_PI) << " deg";
    std::string info = oss.str();

    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glRasterPos2f(20, WINDOW_HEIGHT - 40);
    std::string controls = "Controls: SPACE - pause, R - reset";
    for (char c : controls) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void PendulumModule::handleInput(unsigned char key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
    case ' ':
        isRunning = !isRunning;
        std::cout << "Pendulum: isRunning=" << isRunning << std::endl;
        break;
    case 'r':
    case 'R':
        init();
        break;
    }
}

void PendulumModule::handleSpecialInput(int key, int x, int y) {
    (void)key; (void)x; (void)y;
}

void PendulumModule::drawSpring(float startX, float startY, float endX, float endY, int coils) {
    float dx = endX - startX;
    float dy = endY - startY;
    float length = sqrt(dx * dx + dy * dy);

    if (length < 0.001f) return;

    dx /= length;
    dy /= length;

    const float amplitude = 8.0f;

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 50; i++) {
        float t = static_cast<float>(i) / 50.0f;
        float along = t * length;
        float perpendicular = sin(t * static_cast<float>(coils) * 2.0f * M_PI) * amplitude;

        float px = startX + dx * along - dy * perpendicular;
        float py = startY + dy * along + dx * perpendicular;

        glVertex2f(px, py);
    }
    glEnd();
}