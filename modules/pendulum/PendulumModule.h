#pragma once
#include "../../core/IModule.h"
#include <vector>
#include <utility>

class PendulumModule : public IModule {
public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleSpecialInput(int key, int x, int y) override;
    const char* getName() override { return "Spring Pendulum"; }

private:
    // Параметры маятника
    float positionR;
    float angle;
    float velocityR;
    float angularVelocity;
    bool isRunning;
    std::vector<std::pair<float, float>> trajectory;

    // Константы физики
    static constexpr float GRAVITY = 9.8f;
    static constexpr float SPRING_CONSTANT = 20.0f;
    static constexpr float MASS = 1.0f;
    static constexpr float REST_LENGTH = 250.0f;
    static constexpr int MAX_TRAJECTORY_POINTS = 500;
    static constexpr float WINDOW_WIDTH = 800.0f;
    static constexpr float WINDOW_HEIGHT = 600.0f;
    const float pivotX = 400.0f;
    const float pivotY = 10.0f;

    // Цвета для отрисовки
    const float SPRING_COLOR[3] = { 0.5f, 0.5f, 0.5f };
    const float MASS_COLOR[3] = { 1.0f, 0.0f, 0.0f };
    const float TRAJECTORY_COLOR[3] = { 0.0f, 0.0f, 1.0f };
    const float AXIS_COLOR[3] = { 0.0f, 0.0f, 0.0f };
    const float GRID_COLOR[3] = { 0.8f, 0.8f, 0.8f };

    void drawSpring(float startX, float startY, float endX, float endY, int coils);
};