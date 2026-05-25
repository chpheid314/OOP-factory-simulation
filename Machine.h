#pragma once

#include <string>
#include <queue>
#include <memory>

#include "SimulationObject.h"
#include "Product.h"
#include "IMachineState.h"

class Machine : public SimulationObject {
public:
    Machine(const std::string& name,
        int processTime);
    virtual ~Machine() = default;

    virtual void update(
        int tick,
        const SimulationSettings& settings
    ) override;

    virtual void process(Product& product) = 0;

    virtual std::string getInfo() const override;

    virtual std::string getName() const override;

    std::string getStateString() const;

    std::string getState() const;

    int getQueueSize() const;
    int getOutputCount() const;

    float getHealth() const;
    float getProgress() const;

    void pushProduct(const Product& product);

    void forceBreak();
    void forceRepair();

    bool hasOutputProduct() const;

    Product popOutputProduct();

    virtual void setProcessingTime(
        int time
    );

    virtual void resetProcessingTime();

    virtual void breakMachine();

    virtual bool isBroken() const;

    void setState(
        std::unique_ptr<IMachineState> state
    );

    void setIdle();

    void setWorking();

    void setBroken();

    bool hasQueue() const;

    Product& currentProduct();

    friend class IdleState;
    friend class WorkingState;
    friend class BrokenState;

protected:
    std::string name;

    std::unique_ptr<IMachineState> machineState;

    float health;

    int processTime;
    int progress;

    int repairTimer;

    std::queue<Product> queue;

    bool hasFinishedProduct;

    Product finishedProduct;

    int outputCount;

    int defaultProcessTime;

    bool broken=false;
};