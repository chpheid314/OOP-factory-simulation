#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Factory.h"
//#include "../UI/UIEventListener.h"
#include "EventManager.h"
#include "logger.h"

int main() {

    srand(time(nullptr));

    EventManager eventBus;

    Logger::getInstance().init("app.log");
    eventBus.subscribe(&Logger::getInstance());

    //UIEventListener ui;
    //eventBus.subscribe(&ui);
    Factory factory(eventBus);
    // Scenario setting
    //factory.getSettings().enableBreakdown = false;

     factory.start();

    for (int i = 0; i < 30; i++) {

        factory.update();

        eventBus.emit({
            EventType::INFO,
            "Tick: " + std::to_string(factory.getTick())
        });

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    return 0;
}