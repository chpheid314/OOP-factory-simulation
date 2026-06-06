#pragma once

#include "Machine.h"

class SheetMachine : public Machine {
public:
    SheetMachine();

    virtual void process(Product& product) override;

    std::string getDescription() const;
};