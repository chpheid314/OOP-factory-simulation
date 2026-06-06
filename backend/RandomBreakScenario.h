#pragma once

#include "Scenario.h"

class RandomBreakScenario
    : public Scenario
{
public:

    void apply(
        ProductionLine& line,
        int tick,
        const SimulationSettings& settings
    ) override;

    void reset(
        ProductionLine& line,
        int tick,
        const SimulationSettings& settings
    ) override;
};