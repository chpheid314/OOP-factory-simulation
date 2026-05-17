#pragma once

#include "Machine.h"

class SheetMachine : public Machine {
public:
    SheetMachine();

    virtual void process(Product& product) override;

    virtual std::string getName() const override;
};