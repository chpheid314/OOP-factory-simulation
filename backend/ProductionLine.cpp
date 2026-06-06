#include "ProductionLine.h"

#include "SheetMachine.h"
#include "CreamMachine.h"
#include "ToppingMachine.h"

ProductionLine::ProductionLine()
{
    reset();
}

void ProductionLine::reset()
{
    machines.clear();

    machines.push_back(
        std::make_unique<SheetMachine>()
    );

    machines.push_back(
        std::make_unique<CreamMachine>()
    );

    machines.push_back(
        std::make_unique<ToppingMachine>()
    );

    hasCompletedProduct=false;
}

void ProductionLine::update(
    int tick,
    const SimulationSettings& settings
)
{
    for(auto& machine : machines)
    {
        machine->update(
            tick,
            settings
        );
    }

    for(size_t i=0;
        i<machines.size()-1;
        i++)
    {
        if(machines[i]->hasOutputProduct())
        {
            Product p=
                machines[i]
                ->popOutputProduct();

            machines[i+1]
                ->pushProduct(p);
        }
    }

    auto& lastMachine=
        machines.back();

    if(lastMachine->hasOutputProduct())
    {
        completedProduct=
            lastMachine
            ->popOutputProduct();

        hasCompletedProduct=true;
    }
}

void ProductionLine::pushProduct(
    const Product& product
)
{
    if(!machines.empty())
    {
        machines[0]
            ->pushProduct(product);
    }
}

bool ProductionLine::hasFinishedProduct() const
{
    return hasCompletedProduct;
}

Product ProductionLine::popFinishedProduct()
{
    hasCompletedProduct=false;

    return completedProduct;
}

std::vector<std::unique_ptr<Machine>>&
ProductionLine::getMachines()
{
    return machines;
}