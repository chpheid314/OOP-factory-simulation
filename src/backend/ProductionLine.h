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

private:
    std::vector<std::unique_ptr<Machine>> machines;

    bool hasCompletedProduct;
    Product completedProduct;
};