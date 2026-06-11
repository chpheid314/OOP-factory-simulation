#pragma once

#include "IMachineState.h"

class WorkingState : public IMachineState
{
public:

    void update(
        Machine& machine,
        int tick
    ) override;

    const char* getName() const override;
};