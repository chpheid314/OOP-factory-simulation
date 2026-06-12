#include "RandomBreakScenario.h"

#include <cstdlib>

#include "ProductionLine.h"
#include "EventManager.h"
#include "Event.h"

RandomBreakScenario::RandomBreakScenario(
    StatisticsManager* statistics,
    EventManager* eventBus
) : statistics(statistics),
      eventBus(eventBus)
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
                    if(machine->forceBreak())
        {
            statistics->addBreakdown();

            if(eventBus)
            {
                eventBus->emit({
                    EventType::MACHINE_BREAKDOWN,
                    machine->getName() +
                    " machine broke down (random)"
                });
            }
        }
        }
    }
}

void RandomBreakScenario::reset(
    ProductionLine& line
)
{
}