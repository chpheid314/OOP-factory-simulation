#pragma once

#include "ScenarioManager.h"

class OverflowScenario
    : public Scenario
{
public:

    void apply(
        ProductionLine& line
    ) override;

    void reset(
        ProductionLine& line
    ) override;
};