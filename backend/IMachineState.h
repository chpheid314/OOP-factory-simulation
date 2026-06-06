#pragma once
#include "SimulationSettings.h"

class Machine;

class IMachineState
{
public:

    virtual ~IMachineState() = default;

    virtual void update(
        Machine& machine,
        int tick,
        const SimulationSettings& settings
    ) = 0;

    virtual const char* getName() const = 0;
};