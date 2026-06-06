#include "IdleState.h"
#include "Machine.h"

void IdleState::update(
    Machine& machine,
    int tick,
    const SimulationSettings& settings
)
{
    if(machine.hasQueue())
    {
        machine.setWorking();
    }
}
const char*
IdleState::getName() const
{
    return "IDLE";
}