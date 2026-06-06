#pragma once

#include "IMachineState.h"

class WorkingState : public IMachineState
{
public:

    void update(
        Machine& machine,
        int tick,
        const SimulationSettings& settings
    ) override;

    const char* getName() const override;
};