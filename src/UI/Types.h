#pragma once

#include "../backend/CakeType.h"

enum class ScenarioType {
    NORMAL_FLOW,
    RANDOM_BREAKDOWNS,
    BOTTLENECK,
    OVERFLOW
};

enum class MachineVisualState {
    IDLE,
    WORKING,
    BROKEN
};