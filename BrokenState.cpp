#include "BrokenState.h"
#include "Machine.h"

void BrokenState::update(
    Machine& machine,
    int
)
{
    machine.repairTimer++;

    if(machine.repairTimer>=5)
    {
        machine.repairTimer=0;

        machine.broken=false;

        machine.setIdle();
    }
}

const char*
BrokenState::getName() const
{
    return "BROKEN";
}