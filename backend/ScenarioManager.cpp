#include "ScenarioManager.h"
#include "ProductionLine.h"
#include "SimulationSettings.h"

void ScenarioManager::addScenario(
    std::unique_ptr<Scenario> scenario
)
{
    scenarios.push_back(
        std::move(scenario)
    );
}

void ScenarioManager::apply(
    ProductionLine& line, int tick, const SimulationSettings& settings
)
{
    for(auto& scenario : scenarios)
    {
        if(scenario->isEnabled())
        {
            scenario->apply(line, tick, settings);
        }
    }
}

void ScenarioManager::reset(
    ProductionLine& line, int tick, const SimulationSettings& settings
)
{
    for(auto& scenario : scenarios)
    {
        scenario->reset(line, tick, settings);
    }
}