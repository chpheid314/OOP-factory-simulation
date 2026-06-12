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

    scenarioManager.addScenario(
        std::make_unique<RandomBreakScenario>(
            &statistics,
            &eventBus
        )
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
        line
    );

    line.update(
        tick
    );

    for(auto& machine : line.getMachines())
    {
        if(machine->consumeAutoRepairFlag())
        {
            eventBus.emit({
                EventType::MACHINE_REPAIRED,
                machine->getName()
                + " machine repaired automatically"
            });
        }
    }

    int overflowLost =
        line.consumeOverflowLostCount();

    for(
        int i = 0;
        i < overflowLost;
        i++
    )
    {
        statistics.addLost();
    }

    if(line.hasFinishedProduct())
    {
        Product p= line.popFinishedProduct();

        if(p.isBurned())
        {
            statistics.addLost();

            eventBus.emit({
                EventType::PRODUCT_LOST,
                "Product " +
                std::to_string(p.getId()) +
                " burned! Quality: " +
                std::to_string(p.getQuality())
            });
        }
        else
        {
            statistics.addFinished();

            eventBus.emit({
                EventType::PRODUCT_DONE,
                "Product " + std::to_string(p.getId()) +
                " completed! Quality: " + std::to_string(p.getQuality())
            });
        }
    }
}

void Factory::reset()
{
    running = false;

    line.reset();

    tick = 0;

    statistics.reset();

    scenarioManager.reset(line);
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

    return statistics.getFinishedCount();
}

int Factory::getLostCount() const {

    return statistics.getLostCount();
}

int Factory::getBreakdownCount() const {

    return statistics.getBreakdownCount();
}

std::vector<std::unique_ptr<Machine>>& Factory::getMachines() {

    return line.getMachines();
}

ProductionLine& Factory::getProductionLine()
{
    return line;
}

void Factory::addBreakdown()
{
    statistics.addBreakdown();
}

ScenarioManager& Factory::getScenarioManager()
{
    return scenarioManager;
}

int Factory::getWipCount() const
{
    return line.getWipCount();
}