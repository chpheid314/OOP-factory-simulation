#include "EventManager.h"

void EventManager::subscribe(IEventListener* listener) {
    listeners.push_back(listener);
}

void EventManager::emit(const Event& event) {
    for (auto* l : listeners) {
        l->onEvent(event);
    }
}