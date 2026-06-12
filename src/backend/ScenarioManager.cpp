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

bool ScenarioManager::isEnabled(
    int index
) const
{
    if(index < 0 ||
       index >= scenarios.size())
    {
        return false;
    }

    return scenarios[index]->isEnabled();
}

void ScenarioManager::setEnabled(
    int index,
    bool enabled
)
{
    if(index < 0 ||
       index >= scenarios.size())
    {
        return;
    }

    scenarios[index]->setEnabled(
        enabled
    );
}
