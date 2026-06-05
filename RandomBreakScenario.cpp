#include "RandomBreakScenario.h"

#include <cstdlib>

#include "ProductionLine.h"

RandomBreakScenario::RandomBreakScenario(
    StatisticsManager* statistics
)
    : statistics(statistics)
{
}

void RandomBreakScenario::apply(
    ProductionLine& line
)
{
    auto& machines=
        line.getMachines();

    for(auto& machine : machines)
    {
        if(rand()%100<2)
        {
            machine->breakMachine();

            if(statistics)
            {
                statistics->addBreakdown();
            }
        }
    }
}

void RandomBreakScenario::reset(
    ProductionLine&
)
{
}