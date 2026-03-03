#pragma once
#include "../../core/IModule.h"

class RotatingCubeModule : public IModule {
public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleSpecialInput(int key, int x, int y) override;
    const char* getName() override { return "Rotating Cube"; }

private:
    float angleX;
    float angleY;
    int autoRotate;
    int wireframeMode;

    void drawCube();
};