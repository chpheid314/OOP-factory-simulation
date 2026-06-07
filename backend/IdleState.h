#pragma once

#include "IMachineState.h"

class IdleState : public IMachineState
{
public:

    void update(
        Machine& machine,
        int tick
    ) override;

    const char* getName() const override;
};