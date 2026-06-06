#include "Factory.h"
#include "Event.h"
#include "EventManager.h"

#include "SheetMachine.h"
#include "CreamMachine.h"
#include "ToppingMachine.h"

#include "RandomBreakScenario.h"
#include "BottleneckScenario.h"
#include "OverflowScenario.h"

#include "Product.h"

#include <iostream>


Factory::Factory(EventManager& bus) : eventBus(bus) {

    tick = 0;

    running = false;

    currentRecipe = CakeType::CHOCOLATE;

    nextProductId = 1;

    finishedCount = 0;
    lostCount = 0;
    breakdownCount = 0;

    scenarioManager.addScenario(
    std::make_unique<RandomBreakScenario>()
    );

    scenarioManager.addScenario(
    std::make_unique<BottleneckScenario>()
    );

    scenarioManager.addScenario(
    std::make_unique<OverflowScenario>()
    );
}

void Factory::update() {

    if (!running)
        return;

    tick++;

    if (tick % 4 == 0) {

        spawnProduct();
    }

    scenarioManager.apply(
        line, tick, settings
    );

    line.update(
        tick,
        settings
    );

    if(line.hasFinishedProduct())
    {
        Product p=
            line.popFinishedProduct();

        finishedCount++;

        eventBus.emit({
            EventType::PRODUCT_DONE,
            "Product " + std::to_string(p.getId()) +
            " completed! Quality: " + std::to_string(p.getQuality())
        });
    }
}

void Factory::reset() {

    line.reset();

    tick = 0;

    finishedCount = 0;
    lostCount = 0;
    breakdownCount = 0;

    scenarioManager.reset(
        line, tick, settings
    );
}

void Factory::start() {

    running = true;

      eventBus.emit({
        EventType::INFO,
        "Factory started"
    });
}

void Factory::pause() {

    running = false;

    eventBus.emit({
        EventType::INFO,
        "Factory paused"
    });
}

bool Factory::isRunning() const {

    return running;

    
}

void Factory::spawnProduct() {

    Product p(nextProductId++, currentRecipe);

    line.pushProduct(p);
}

void Factory::setRecipe(CakeType type) {

    currentRecipe = type;
}

CakeType Factory::getRecipe() const {

    return currentRecipe;
}

int Factory::getTick() const {

    return tick;
}

int Factory::getFinishedCount() const {

    return finishedCount;
}

int Factory::getLostCount() const {

    return lostCount;
}

int Factory::getBreakdownCount() const {

    return breakdownCount;
}

std::vector<std::unique_ptr<Machine>>& Factory::getMachines() {

    return line.getMachines();
}

SimulationSettings& Factory::getSettings() {

    return settings;
}

ProductionLine& Factory::getProductionLine()
{
    return line;
}