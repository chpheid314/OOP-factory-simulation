#include "Factory.h"

#include <iostream>

#include "SheetMachine.h"
#include "CreamMachine.h"
#include "ToppingMachine.h"
#include "RandomBreakScenario.h"
#include "BottleneckScenario.h"
#include "OverflowScenario.h"

Factory::Factory() {

    tick = 0;

    running = false;

    currentRecipe = CakeType::CHOCOLATE;

    nextProductId = 1;

    scenarioManager.addScenario(
        std::make_unique<RandomBreakScenario>(
            &statistics
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

    if(line.hasFinishedProduct())
    {
        Product p= line.popFinishedProduct();

        if(p.isBurned())
        {
            statistics.addLost();

            std::cout
                << "Product "
                << p.getId()
                << " burned! Quality: "
                << p.getQuality()
                << std::endl;
        }
        else
        {
            statistics.addFinished();

            std::cout
                << "Product "
                << p.getId()
                << " completed! Quality: "
                << p.getQuality()
                << std::endl;
        }
    }
}

void Factory::reset()
{
    line.reset();

    tick = 0;

    statistics.reset();

    scenarioManager.reset(line);
}

void Factory::start() {

    running = true;
}

void Factory::pause() {

    running = false;
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