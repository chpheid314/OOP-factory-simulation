#pragma once

#include "Machine.h"

class CreamMachine : public Machine {
public:
    CreamMachine();

    virtual void process(Product& product) override;

    virtual std::string getName() const override;
};