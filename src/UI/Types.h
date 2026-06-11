#pragma once

#include "../backend/CakeType.h"

enum class ScenarioType {
    NORMAL_FLOW,
    BOTTLENECK,
    RANDOM_BREAKDOWNS,
    OVERFLOW
};

enum class MachineVisualState {
    IDLE,
    WORKING,
    BROKEN
};