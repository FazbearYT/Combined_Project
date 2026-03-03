#pragma once

// Базовый класс для всех модулей
class IModule {
public:
    virtual ~IModule() {}
    virtual void init() = 0;
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void handleInput(unsigned char key, int x, int y) = 0;
    virtual void handleSpecialInput(int key, int x, int y) = 0;
    virtual const char* getName() = 0;
};