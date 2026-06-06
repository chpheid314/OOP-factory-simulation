#pragma once

#include <memory>
#include <vector>

#include "Scenario.h"

class ProductionLine;

class ScenarioManager
{
public:

    void addScenario(
        std::unique_ptr<Scenario> scenario
    );

    void apply(
        ProductionLine& line, int tick, const SimulationSettings& settings
    );

    void reset(
        ProductionLine& line, int tick, const SimulationSettings& settings
    );

private:

    std::vector<
        std::unique_ptr<Scenario>
    > scenarios;
};