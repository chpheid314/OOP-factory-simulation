#include "IdleState.h"
#include "Machine.h"

void IdleState::update(
    Machine& machine,
    int
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