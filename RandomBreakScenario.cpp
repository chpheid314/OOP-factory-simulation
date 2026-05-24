#include "RandomBreakScenario.h"

#include <cstdlib>

#include "ProductionLine.h"

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
        }
    }
}

void RandomBreakScenario::reset(
    ProductionLine&
)
{
}