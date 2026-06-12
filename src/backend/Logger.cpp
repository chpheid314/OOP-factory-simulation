#include "Logger.h"
#include <iostream>

Logger::Logger() {}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& filename) {
    file.open(filename, std::ios::app);
}

void Logger::onEvent(const Event& event) {

    std::lock_guard<std::mutex> lock(mtx);

    std::string typeStr;

    switch (event.type) {
        case EventType::INFO: typeStr = "[INFO]"; break;
        case EventType::WARNING: typeStr = "[WARN]"; break;
        case EventType::ERROR: typeStr = "[ERROR]"; break;
        case EventType::PRODUCT_DONE: typeStr = "[DONE]"; break;
        case EventType::MACHINE_BREAKDOWN: typeStr = "[BREAK]"; break;
        case EventType::PRODUCT_LOST: typeStr = "[LOST]"; break;
        case EventType::MACHINE_REPAIRED: typeStr = "[REPAIR]"; break;
    }

    std::string out = typeStr + " " + event.message;

    if (file.is_open()) {
        file << out << std::endl;
    } else {
        std::cout << out << std::endl;
    }
}