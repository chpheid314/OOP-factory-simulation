#pragma once

#include "Machine.h"

class CreamMachine : public Machine {
public:
    CreamMachine();

    virtual void process(Product& product) override;

    std::string getDescription() const;
};