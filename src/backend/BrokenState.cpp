#include "BrokenState.h"
#include "Machine.h"

void BrokenState::update(
    Machine& machine,
    int tick
)
{
    machine.repairTimer++;

    if(machine.repairTimer>=10)
    {
        machine.repairTimer=0;

        machine.broken=false;

        machine.health = 100.0f;

        machine.autoRepaired = true;

        machine.setIdle();
    }
}

const char*
BrokenState::getName() const
{
    return "BROKEN";
}