#pragma once
#include "../../core/IModule.h"

class WaveSurfaceModule : public IModule {
public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleSpecialInput(int key, int x, int y) override;
    const char* getName() override { return "Wave Surface"; }

private:
    float gTime;
    float gSpeed;
    float gAmp;
    float gRot;
    bool gPause;
    int winWidth;
    int winHeight;

    float func(float x, float y);
    void project(float x, float y, float z, float& sx, float& sy);
};