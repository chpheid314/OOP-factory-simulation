#include "WorkingState.h"
#include "Machine.h"

void WorkingState::update(
    Machine& machine,
    int tick
)
{
    machine.progress++;

    if(machine.progress>=
       machine.processTime)
    {
        Product current=
            machine.currentProduct();

        machine.queue.pop();

        machine.process(current);

        machine.finishedProduct=
            current;

        machine.hasFinishedProduct=
            true;

        machine.outputCount++;

        machine.progress=0;

        machine.setIdle();
    }
}

const char*
WorkingState::getName() const
{
    return "WORKING";
}