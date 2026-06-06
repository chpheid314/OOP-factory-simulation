#pragma once

#include "Scenario.h"

class BottleneckScenario
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