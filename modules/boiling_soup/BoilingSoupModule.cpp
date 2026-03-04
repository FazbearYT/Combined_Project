#include "BoilingSoupModule.h"
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void BoilingSoupModule::init() {
    T_dna = 20.0f;
    T_vody = 20.0f;
    koeff = 0.001f;
    frameCount = 0;
    bubbles.clear();

    std::cout << "[BoilingSoup] INIT" << std::endl;
}

void BoilingSoupModule::update(float dt) {
    frameCount++;

    T_vody += (T_dna - T_vody) * koeff;
    if (T_vody > 100.0f) T_vody = 100.0f;

    // Создаем пузырьки (4 попытки за кадр)
    for (int i = 0; i < 4; i++) {
        int threshold = static_cast<int>(T_vody) - 20;
        if (threshold > 0 && (rand() % 100) < threshold) {
            Bubble b;
            b.x = (rand() % 800) - 400;
            b.y = -300;
            b.size = 1;
            bubbles.push_back(b);
        }
    }

    // Двигаем пузырьки
    for (size_t i = 0; i < bubbles.size(); i++) {
        bubbles[i].y += 5;

        if (frameCount % 3 == 0) {
            bubbles[i].size += 1;
        }

        if (bubbles[i].y > 300 + bubbles[i].size) {
            bubbles.erase(bubbles.begin() + static_cast<long>(i));
            if (i > 0) i--;
        }
    }

    if (frameCount % 120 == 0) {
        std::cout << "[BoilingSoup] T_vody=" << T_vody
            << ", Bubbles=" << bubbles.size() << std::endl;
    }
}

void BoilingSoupModule::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400.0f, 400.0f, -300.0f, 300.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Фон (синий)
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-400.0f, -300.0f);
    glVertex2f(400.0f, -300.0f);
    glVertex2f(400.0f, 300.0f);
    glVertex2f(-400.0f, 300.0f);
    glEnd();
    glPopMatrix();

    // Пузырьки (желтые - чтобы было видно!)
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 0.0f);

    for (const auto& b : bubbles) {
        drawCircle(
            static_cast<float>(b.x),
            static_cast<float>(b.y),
            static_cast<float>(b.size)
        );
    }
    glPopMatrix();

    // Текст (черный)
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-390.0f, -290.0f);

    std::ostringstream oss;
    oss << "T_dna: " << T_dna << "C | T_vody: " << T_vody
        << "C | Bubbles: " << bubbles.size();
    std::string info = oss.str();

    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glRasterPos2f(-390.0f, 270.0f);
    std::string controls = "+ heat | - cool | R reset";
    for (char c : controls) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }
    glPopMatrix();
}

void BoilingSoupModule::handleInput(unsigned char key, int x, int y) {
    (void)x; (void)y;
    switch (key) {
    case '+':
        T_dna += 5.0f;
        if (T_dna > 200.0f) T_dna = 200.0f;
        std::cout << "[BoilingSoup] T_dna=" << T_dna << std::endl;
        break;
    case '-':
        T_dna -= 5.0f;
        if (T_dna < 10.0f) T_dna = 10.0f;
        std::cout << "[BoilingSoup] T_dna=" << T_dna << std::endl;
        break;
    case 'r':
    case 'R':
        init();
        break;
    }
}

void BoilingSoupModule::handleSpecialInput(int key, int x, int y) {
    (void)key; (void)x; (void)y;
}

void BoilingSoupModule::drawCircle(float x, float y, float radius) {
    if (radius < 1.0f) radius = 1.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 50; i++) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / 50.0f;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}