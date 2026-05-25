#include <sstream>
#include "Machine.h"
#include "IdleState.h"
#include "WorkingState.h"
#include "BrokenState.h"

Machine::Machine(const std::string& name,
                 int processTime)
    : name(name),
      processTime(processTime),
      defaultProcessTime(processTime)
{

    machineState = std::make_unique<IdleState>();

    health = 100.0f;

    progress = 0;

    broken = false;

    repairTimer = 0;

    outputCount = 0;

    hasFinishedProduct = false;
}

void Machine::update(
    int tick,
    const SimulationSettings&
)
{
    machineState
        ->update(
            *this,
            tick
        );
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

    if (isBroken())
    {
        ss << " | Progress: PAUSED";
    }
    else
    {
        ss << " | Progress: "
        << progressPercent
        << "%";
    }

    return ss.str();
}

std::string Machine::getStateString() const
{
    return machineState
        ->getName();
}

std::string Machine::getState() const
{
    return machineState
        ->getName();
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

    repairTimer = 0;

    setBroken();

    health -= 30;

    if (health < 10)
        health = 10;
}

void Machine::forceRepair() {

    broken = false;

    repairTimer = 0;

    setIdle();

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

void Machine::setProcessingTime(
    int time
)
{
    processTime = time;
}

void Machine::resetProcessingTime()
{
    processTime = defaultProcessTime;
}

void Machine::breakMachine()
{
    forceBreak();
}

void Machine::setState(
    std::unique_ptr<IMachineState> state
)
{
    machineState =
        std::move(state);
}

void Machine::setIdle()
{
    machineState=
        std::make_unique<IdleState>();
}

void Machine::setWorking()
{
    machineState=
        std::make_unique<WorkingState>();
}

void Machine::setBroken()
{
    machineState=
        std::make_unique<BrokenState>();
}

bool Machine::hasQueue() const
{
    return !queue.empty();
}

Product& Machine::currentProduct()
{
    return queue.front();
}