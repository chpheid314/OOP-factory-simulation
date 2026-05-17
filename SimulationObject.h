#pragma once
#include <string>
#include "SimulationSettings.h"

class SimulationObject {
public:
    virtual void update(
        int tick,
        const SimulationSettings& settings
    ) = 0;
    virtual std::string getInfo() const = 0;
    virtual std::string getName() const = 0;

    virtual ~SimulationObject() = default;

protected:
    int objectId;
};