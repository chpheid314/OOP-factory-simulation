#pragma once

#include <memory>
#include <vector>

#include "Scenario.h"

class ScenarioManager
{
public:

    void addScenario(
        std::unique_ptr<Scenario> scenario
    );

    void apply(
        ProductionLine& line
    );

    void reset(
        ProductionLine& line
    );

    bool isEnabled(
        int index
    ) const;

    void setEnabled(
        int index,
        bool enabled
    );

    int getScenarioCount() const;

private:

    std::vector<
        std::unique_ptr<Scenario>
    > scenarios;
};