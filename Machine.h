#pragma once

#include <string>
#include <queue>

#include "SimulationObject.h"
#include "MachineState.h"
#include "Product.h"

class Machine : public SimulationObject {
public:
    Machine(const std::string& name,
        int processTime,
        float breakChance);
    virtual ~Machine() = default;

    virtual void update(
        int tick,
        const SimulationSettings& settings
    ) override;

    virtual void process(Product& product) = 0;

    virtual std::string getInfo() const override;

    virtual std::string getName() const override;

    std::string getStateString() const;

    MachineState getState() const;

    int getQueueSize() const;
    int getOutputCount() const;

    float getHealth() const;
    float getProgress() const;

    bool isBroken() const;

    void pushProduct(const Product& product);

    void forceBreak();
    void forceRepair();

    bool hasOutputProduct() const;

    Product popOutputProduct();

protected:
    std::string name;

    MachineState state;

    float health;

    int processTime;
    int progress;

    bool broken;

    int repairTimer;

    std::queue<Product> queue;

    bool hasFinishedProduct;

    Product finishedProduct;

    int outputCount;

    float breakChance;
};