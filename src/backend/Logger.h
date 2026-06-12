#pragma once

#include <fstream>
#include <mutex>
#include "IEventListener.h"

class Logger : public IEventListener {
private:
    std::ofstream file;
    std::mutex mtx;

    Logger();

public:
    static Logger& getInstance();

    void init(const std::string& filename);

    void onEvent(const Event& event) override;
};