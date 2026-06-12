#pragma once

#include "Types.h"
#include <string>
#include <vector>

struct MachineSnap {
    std::string name;
    
    MachineVisualState state = MachineVisualState::IDLE;

    float progress = 0.0f;
    bool burned = false;
    float health = 1.0f;
    int queueDepth = 0;
    int outputCount = 0;
    float processTime = 0.0f;
    float conveyorLoad = 0.0f;
    bool finiteQueue = false;
};

struct FactorySnap {
    int tick = 0;
    bool running = false;
    float speed = 1.0f;

    ScenarioType scenario = ScenarioType::NORMAL_FLOW;
    CakeType recipe = CakeType::MATCHA;

    float conveyorLoad = 0.0f;
    int finishedCount = 0;
    int lostCount = 0;
    int breakdownCount = 0;
    int wipCount = 0;

    std::vector<std::string> logs;

    MachineSnap sheet {"Sheet"};
    MachineSnap cream {"Cream"};
    MachineSnap topping {"Topping"};
};