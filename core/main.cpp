#include "App.h"
#include "../modules/pendulum/PendulumModule.h"
#include "../modules/boiling_soup/BoilingSoupModule.h"
#include "../modules/wave_surface/WaveSurfaceModule.h"
#include "../modules/rotating_cube/RotatingCubeModule.h"
#include <iostream>
#include <windows.h>

int main(int argc, char** argv) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "========================================" << std::endl;
    std::cout << "   MULTI-PROJECT GRAPHICS LAB" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    std::cout << "Модули:" << std::endl;
    std::cout << "  1 - Spring Pendulum (Пружинный маятник)" << std::endl;
    std::cout << "  2 - Boiling Soup (Кипящий суп)" << std::endl;
    std::cout << "  3 - Wave Surface (Волновая поверхность)" << std::endl;
    std::cout << "  4 - Rotating Cube (Вращающийся куб)" << std::endl << std::endl;
    std::cout << "Клавиши 1-4 - переключение модулей" << std::endl;
    std::cout << "ESC - выход" << std::endl;
    std::cout << "========================================" << std::endl;

    auto& app = App::getInstance();

    app.registerModule(std::make_shared<PendulumModule>());
    app.registerModule(std::make_shared<BoilingSoupModule>());
    app.registerModule(std::make_shared<WaveSurfaceModule>());
    app.registerModule(std::make_shared<RotatingCubeModule>());

    app.setActiveSheet(0);

    app.run(argc, argv);
    return 0;
}