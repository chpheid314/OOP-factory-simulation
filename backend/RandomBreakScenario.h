#pragma once

#include "Scenario.h"
#include "StatisticsManager.h"

class RandomBreakScenario
    : public Scenario
{
public:
    explicit RandomBreakScenario(
        StatisticsManager* statistics
    );
    void apply(
        ProductionLine& line
    ) override;

    void reset(
        ProductionLine& line
    ) override;
private:
    StatisticsManager* statistics;
};