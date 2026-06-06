#pragma once

#include "IMachineState.h"
#include "SimulationSettings.h"

class IdleState : public IMachineState
{
public:

    void update(
        Machine& machine,
        int tick,
        const SimulationSettings& settings
    ) override;

    const char* getName() const override;
};