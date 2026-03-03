#pragma once
#include "../../core/IModule.h"
#include <vector>

struct Bubble {
    float x, y;
    float size;
};

class BoilingSoupModule : public IModule {
public:
    void init() override;
    void update(float dt) override;
    void render() override;
    void handleInput(unsigned char key, int x, int y) override;
    void handleSpecialInput(int key, int x, int y) override;
    const char* getName() override { return "Boiling Soup"; }

private:
    float T_dna;
    float T_vody;
    float koeff;
    int frameCount;
    std::vector<Bubble> bubbles;

    static constexpr float WINDOW_WIDTH = 800.0f;
    static constexpr float WINDOW_HEIGHT = 600.0f;

    void drawCircle(float x, float y, float radius);
};