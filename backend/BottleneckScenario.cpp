#include "BottleneckScenario.h"

#include "ProductionLine.h"

void BottleneckScenario::apply(
    ProductionLine& line,
    int tick,
    const SimulationSettings& settings
)
{
    auto& machines=
        line.getMachines();

    if(machines.size()>1)
    {
        machines[1]->setProcessingTime(10);
    }
}

void BottleneckScenario::reset(
    ProductionLine& line,
    int tick,
    const SimulationSettings& settings
)
{
    auto& machines=
        line.getMachines();

    if(machines.size()>1)
    {
        machines[1]->resetProcessingTime();
    }
}