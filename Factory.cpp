#include "Factory.h"

#include <iostream>

#include "SheetMachine.h"
#include "CreamMachine.h"
#include "ToppingMachine.h"

Factory::Factory() {

    tick = 0;

    running = false;

    currentRecipe = CakeType::CHOCOLATE;

    nextProductId = 1;

    finishedCount = 0;
    lostCount = 0;
    breakdownCount = 0;

    machines.push_back(std::make_unique<SheetMachine>());
    machines.push_back(std::make_unique<CreamMachine>());
    machines.push_back(std::make_unique<ToppingMachine>());
}

void Factory::update() {

    if (!running)
        return;

    tick++;

    if (tick % 4 == 0) {

        spawnProduct();
    }

    for (auto& machine : machines) {

        machine->update(tick, settings);
    }

    if (machines[0]->hasOutputProduct()) {

        Product p = machines[0]->popOutputProduct();

        machines[1]->pushProduct(p);
    }

    if (machines[1]->hasOutputProduct()) {

        Product p = machines[1]->popOutputProduct();

        machines[2]->pushProduct(p);
    }

    if (machines[2]->hasOutputProduct()) {

        Product p = machines[2]->popOutputProduct();

        finishedCount++;

        std::cout
            << "Product "
            << p.getId()
            << " completed! Quality: "
            << p.getQuality()
            << std::endl;
    }
}

void Factory::reset() {

    machines.clear();

    machines.push_back(std::make_unique<SheetMachine>());
    machines.push_back(std::make_unique<CreamMachine>());
    machines.push_back(std::make_unique<ToppingMachine>());

    tick = 0;

    finishedCount = 0;
    lostCount = 0;
    breakdownCount = 0;
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

    machines[0]->pushProduct(p);
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

    return machines;
}

SimulationSettings& Factory::getSettings() {

    return settings;
}