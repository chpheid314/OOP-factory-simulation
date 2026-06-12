#pragma once

#include "../backend/IEventListener.h"

#include <vector>
#include <string>

class UIEventListener : public IEventListener
{
private:
    std::vector<std::string>& logs;

public:
    UIEventListener(
        std::vector<std::string>& logs
    )
        : logs(logs)
    {
    }

    void onEvent(
        const Event& event
    ) override
    {
        std::string type;

        switch (event.type)
        {
        case EventType::INFO:
            type = "[INFO]";
            break;

        case EventType::WARNING:
            type = "[WARN]";
            break;

        case EventType::ERROR:
            type = "[ERROR]";
            break;

        case EventType::PRODUCT_DONE:
            type = "[DONE]";
            break;

        case EventType::MACHINE_BREAKDOWN:
            type = "[BREAK]";
            break;

        case EventType::MACHINE_REPAIRED:
            type = "[REPAIR]";
            break;

        case EventType::PRODUCT_LOST:
            type = "[LOST]";
            break;
        }
        

        logs.push_back(
            type + " " + event.message
        );
    }
};