#include "Machine.h"
#include <sstream>

Machine::Machine(const std::string& name,
                 int processTime,
                 float breakChance)
    : name(name),
      processTime(processTime),
      breakChance(breakChance)
{
    state = MachineState::IDLE;

    health = 100.0f;

    progress = 0;

    broken = false;

    repairTimer = 0;

    outputCount = 0;

    hasFinishedProduct = false;
}

void Machine::update(int tick, const SimulationSettings& settings) {

    if (broken) {

        repairTimer++;

        if (repairTimer >= 5) {
            broken = false;
            state = MachineState::IDLE;
            repairTimer = 0;
        }

        return;
    }

    if (state == MachineState::WORKING) {

        if (settings.enableBreakdown) {

            float r = (float)rand() / RAND_MAX;

            if (r < breakChance) {

                broken = true;

                state = MachineState::BROKEN;

                repairTimer = 0;

                health -= 25;

                if (health < 10)
                    health = 10;

                return;
            }
        }

        progress++;

        health -= 0.2f;

        if (health < 20)
            health = 20;

        if (progress >= processTime) {

            Product current = queue.front();
            queue.pop();

            process(current);

            finishedProduct = current;

            hasFinishedProduct = true;

            outputCount++;

            progress = 0;

            state = MachineState::IDLE;
        }
    }

    if (!queue.empty() && state == MachineState::IDLE) {

        state = MachineState::WORKING;
    }
}

std::string Machine::getName() const {

    return name;
}

std::string Machine::getInfo() const {

    std::stringstream ss;

    float progressPercent =
        (float)progress / processTime * 100;

    ss << "[" << getStateString() << "] "
       << name
       << " | Queue: "
       << queue.size()
       << " | Health: "
       << health;

    if (state == MachineState::BROKEN) {

        ss << " | Progress: PAUSED";
    }
    else {

        ss << " | Progress: "
           << progressPercent
           << "%";
    }

    return ss.str();
}

std::string Machine::getStateString() const {

    switch (state) {

    case MachineState::IDLE:
        return "IDLE";

    case MachineState::WORKING:
        return "WORKING";

    case MachineState::BROKEN:
        return "BROKEN";

    default:
        return "UNKNOWN";
    }
}

MachineState Machine::getState() const {

    return state;
}

int Machine::getQueueSize() const {

    return queue.size();
}

int Machine::getOutputCount() const {

    return outputCount;
}

float Machine::getHealth() const {

    return health;
}

float Machine::getProgress() const {

    if (processTime == 0)
        return 0;

    return (float)progress / processTime * 100.0f;
}

bool Machine::isBroken() const {

    return broken;
}

void Machine::pushProduct(const Product& product) {

    queue.push(product);
}

void Machine::forceBreak() {

    broken = true;

    state = MachineState::BROKEN;

    repairTimer = 0;

    health -= 30;

    if (health < 10)
        health = 10;
}

void Machine::forceRepair() {

    broken = false;

    state = MachineState::IDLE;

    repairTimer = 0;

    progress = 0;

    health = 100;
}

bool Machine::hasOutputProduct() const {

    return hasFinishedProduct;
}

Product Machine::popOutputProduct() {

    hasFinishedProduct = false;

    return finishedProduct;
}