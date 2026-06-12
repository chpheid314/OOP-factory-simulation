#pragma once

#include <vector>
#include <memory>

#include "Machine.h"

class ProductionLine {
public:
    ProductionLine();

    void update(
        int tick
    );

    void reset();

    void pushProduct(const Product& product);

    bool hasFinishedProduct() const;

    Product popFinishedProduct();

    std::vector<std::unique_ptr<Machine>>& getMachines();

    void setOverflowMode(
        bool enabled
    );

    int consumeOverflowLostCount();

    int getWipCount() const;

private:
    std::vector<std::unique_ptr<Machine>> machines;

    bool hasCompletedProduct = false;
    Product completedProduct;

    bool overflowMode = false;

    int overflowLostCount = 0;
};