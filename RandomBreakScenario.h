#pragma once

#include "Scenario.h"

class RandomBreakScenario
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