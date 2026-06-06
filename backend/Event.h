#pragma once
#include <string>

enum class EventType {
    INFO,
    WARNING,
    ERROR,
    PRODUCT_DONE,
    MACHINE_BREAKDOWN,
    PRODUCT_LOST
};

struct Event {
    EventType type;
    std::string message;
};