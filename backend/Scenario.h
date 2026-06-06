#pragma once
#include "SimulationSettings.h"

class ProductionLine;

class Scenario
{
public:

    virtual ~Scenario()=default;

    virtual void apply(
        ProductionLine& line, int tick, const SimulationSettings& settings
    )=0;

    virtual void reset(
        ProductionLine& line, int tick, const SimulationSettings& settings
    )=0;

    void setEnabled(
        bool value
    );

    bool isEnabled() const;

protected:

    bool enabled=false;
};