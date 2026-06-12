#pragma once

#include <vector>
#include <memory>

#include "Machine.h"
#include "CakeType.h"
#include "ProductionLine.h"
#include "ScenarioManager.h"
#include "EventManager.h"
#include "StatisticsManager.h"

class Factory {
public:
    Factory(EventManager& bus);

    void update();

    void reset();

    void start();
    void pause();

    bool isRunning() const;

    void setRecipe(CakeType type);

    CakeType getRecipe() const;

    int getTick() const;

    int getFinishedCount() const;
    int getLostCount() const;
    int getBreakdownCount() const;

    void addBreakdown();

    std::vector<std::unique_ptr<Machine>>& getMachines();

    ProductionLine& getProductionLine();

    ScenarioManager& getScenarioManager();

    int getWipCount() const;

private:
    ProductionLine line;

    StatisticsManager statistics;

    int tick;

    bool running;

    CakeType currentRecipe;

    int nextProductId;

    ScenarioManager scenarioManager;

    EventManager& eventBus;

    void spawnProduct();
};