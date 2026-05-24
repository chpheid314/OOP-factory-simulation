#pragma once

class ProductionLine;

class Scenario
{
public:

    virtual ~Scenario()=default;

    virtual void apply(
        ProductionLine& line
    )=0;

    virtual void reset(
        ProductionLine& line
    )=0;
};