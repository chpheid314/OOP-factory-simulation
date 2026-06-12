#pragma once

#include "Scenario.h"
#include "StatisticsManager.h"

class EventManager;

class RandomBreakScenario
    : public Scenario
{
public:
    explicit RandomBreakScenario(
        StatisticsManager* statistics,
        EventManager* eventBus
    );
    void apply(
        ProductionLine& line
    ) override;

    void reset(
        ProductionLine& line
    ) override;
private:
    StatisticsManager* statistics;

    EventManager* eventBus;
};