#include "App.h"
#include <GL/freeglut.h>
#include <iostream>
#include <string>

static App* g_appInstance = nullptr;

App& App::getInstance() {
    static App instance;
    return instance;
}

App::App() {
    g_appInstance = this;
}

void App::registerModule(std::shared_ptr<IModule> module) {
    modules.push_back(module);
}

void App::setActiveSheet(int index) {
    if (index >= 0 && index < static_cast<int>(modules.size())) {
        if (activeIndex != index) {
            std::cout << "Switching from module " << activeIndex
                << " to module " << index << std::endl;
            activeIndex = index;
            std::cout << "Calling init() for module: "
                << modules[activeIndex]->getName() << std::endl;
            modules[activeIndex]->init();
        }
    }
}

void displayCallback() {
    g_appInstance->onDisplay();
}

void timerCallback(int v) {
    g_appInstance->onTimer(v);
}

void keyboardCallback(unsigned char k, int x, int y) {
    g_appInstance->onKeyboard(k, x, y);
}

void specialKeyboardCallback(int k, int x, int y) {
    g_appInstance->onSpecialKeyboard(k, x, y);
}

void reshapeCallback(int w, int h) {
    g_appInstance->onReshape(w, h);
}

void App::run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Multi-Project Graphics Lab");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyboardCallback);
    glutReshapeFunc(reshapeCallback);
    glutTimerFunc(16, timerCallback, 0);

    if (!modules.empty()) {
        setActiveSheet(0);
    }

    std::cout << "Application started!" << std::endl;
    glutMainLoop();
}

void App::onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!modules.empty()) {
        modules[activeIndex]->render();
    }

    // Отрисовка интерфейса
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(10, 580);

    std::string info = "Module: ";
    if (!modules.empty()) {
        int num = activeIndex + 1;
        info += std::to_string(num);
        info += " - ";
        info += modules[activeIndex]->getName();
    }
    info += " | Keys: 1-4 switch, ESC exit";

    for (char c : info) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

void App::onTimer(int value) {
    if (!modules.empty()) {
        modules[activeIndex]->update(0.016f);
    }
    glutPostRedisplay();
    glutTimerFunc(16, timerCallback, 0);
}

void App::onKeyboard(unsigned char key, int x, int y) {
    if (key == '1') setActiveSheet(0);
    if (key == '2') setActiveSheet(1);
    if (key == '3') setActiveSheet(2);
    if (key == '4') setActiveSheet(3);
    if (key == 27) {
        std::cout << "Exiting application..." << std::endl;
        exit(0);
    }

    if (!modules.empty()) {
        modules[activeIndex]->handleInput(key, x, y);
    }
}

void App::onSpecialKeyboard(int key, int x, int y) {
    if (!modules.empty()) {
        modules[activeIndex]->handleSpecialInput(key, x, y);
    }
}

void App::onReshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
}