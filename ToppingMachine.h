#pragma once

#include "Machine.h"

class ToppingMachine : public Machine {
public:
    ToppingMachine();

    virtual void process(Product& product) override;

    std::string getDescription() const;
};