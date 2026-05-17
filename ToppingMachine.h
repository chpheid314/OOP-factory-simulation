#pragma once

#include "Machine.h"

class ToppingMachine : public Machine {
public:
    ToppingMachine();

    virtual void process(Product& product) override;

    virtual std::string getName() const override;
};