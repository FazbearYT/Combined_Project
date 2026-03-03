#pragma once
#include "IModule.h"
#include <vector>
#include <memory>

class App {
public:
    static App& getInstance();
    void registerModule(std::shared_ptr<IModule> module);
    void setActiveSheet(int index);
    void run(int argc, char** argv);

    void onDisplay();
    void onTimer(int value);
    void onKeyboard(unsigned char key, int x, int y);
    void onSpecialKeyboard(int key, int x, int y);
    void onReshape(int width, int height);

private:
    App();
    std::vector<std::shared_ptr<IModule>> modules;
    int activeIndex = 0;
    int windowWidth = 800;
    int windowHeight = 600;
};