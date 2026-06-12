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
    ScenarioType scenario = ScenarioType::NORMAL_FLOW;
    CakeType recipe = CakeType::MATCHA;
};