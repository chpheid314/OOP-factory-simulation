#pragma once

#include "IMachineState.h"

class BrokenState : public IMachineState
{
public:

    void update(
        Machine& machine,
        int tick
    ) override;

    const char* getName() const override;
};