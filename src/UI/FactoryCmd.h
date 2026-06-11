#pragma once
#include "Types.h"

struct FactoryCmd
{
    bool start = false;
    bool pause = false;
    bool reset = false;
    bool forceBreak = false;
    bool instantRepair = false;
    bool clearLogs = false;
    int selectedMachine = -1;
    float speed = 1.0f;
    bool bottleneck = false;
    bool randomBreakdowns = false;
    bool overflow = false;
    CakeType recipe = CakeType::MATCHA;
};