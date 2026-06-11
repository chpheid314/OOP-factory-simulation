#pragma once

#include <vector>
#include <memory>
#include "IEventListener.h"
#include "Event.h"

class EventManager {
private:
    std::vector<IEventListener*> listeners;

public:
    void subscribe(IEventListener* listener);

    void emit(const Event& event);
};