#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Factory.h"

int main() {

    srand(time(nullptr));

    Factory factory;

    // Scenario setting
    //factory.getSettings().enableBreakdown = false;

    factory.start();

    for (int i = 0; i < 30; i++) {

        factory.update();

        std::cout << "Tick: "
                  << factory.getTick()
                  << std::endl;

        for (auto& machine : factory.getMachines()) {
            std::cout
                << machine->getInfo()
                << std::endl;
        }

        std::cout << "----------------------" << std::endl;

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    return 0;
}