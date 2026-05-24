#pragma once

#include <vector>
#include <memory>

#include "Machine.h"
#include "CakeType.h"
#include "SimulationSettings.h"
#include "ProductionLine.h"
#include "ScenarioManager.h"

class Factory {
public:
    Factory();

    void update();

    void reset();

    void start();
    void pause();

    bool isRunning() const;

    void spawnProduct();

    void setRecipe(CakeType type);

    CakeType getRecipe() const;

    int getTick() const;

    int getFinishedCount() const;
    int getLostCount() const;
    int getBreakdownCount() const;

    std::vector<std::unique_ptr<Machine>>& getMachines();

    SimulationSettings& getSettings();

    ProductionLine& getProductionLine();

private:
    ProductionLine line;

    int tick;

    bool running;

    CakeType currentRecipe;

    int nextProductId;

    int finishedCount;
    int lostCount;
    int breakdownCount;

    SimulationSettings settings;

    ScenarioManager scenarioManager;
};