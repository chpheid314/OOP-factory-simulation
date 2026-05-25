#include "ScenarioManager.h"
#include "ProductionLine.h"

void ScenarioManager::addScenario(
    std::unique_ptr<Scenario> scenario
)
{
    scenarios.push_back(
        std::move(scenario)
    );
}

void ScenarioManager::apply(
    ProductionLine& line
)
{
    for(auto& scenario : scenarios)
    {
        if(scenario->isEnabled())
        {
            scenario->apply(line);
        }
    }
}

void ScenarioManager::reset(
    ProductionLine& line
)
{
    for(auto& scenario : scenarios)
    {
        scenario->reset(line);
    }
}