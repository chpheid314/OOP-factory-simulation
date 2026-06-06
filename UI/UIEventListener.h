#pragma once

#include "../backend/IEventListener.h"
#include <iostream>

class UIEventListener : public IEventListener {
public:
    void onEvent(const Event& event) override {
        std::string type;

        switch (event.type) {
            case EventType::INFO: type = "[UI INFO]"; break;
            case EventType::WARNING: type = "[UI WARN]"; break;
            case EventType::ERROR: type = "[UI ERROR]"; break;
            case EventType::PRODUCT_DONE: type = "[UI DONE]"; break;
            case EventType::MACHINE_BREAKDOWN: type = "[UI BREAK]"; break;
            case EventType::PRODUCT_LOST: type = "[UI LOST]"; break;
        }

        std::cout << type << " " << event.message << std::endl;
    }
};