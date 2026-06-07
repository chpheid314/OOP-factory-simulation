#pragma once

class Machine;

class IMachineState
{
public:

    virtual ~IMachineState() = default;

    virtual void update(
        Machine& machine,
        int tick
    ) = 0;

    virtual const char* getName() const = 0;
};