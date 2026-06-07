#pragma once

#include "Scenario.h"

class BottleneckScenario
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