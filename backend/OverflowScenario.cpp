#include "OverflowScenario.h"

#include "ProductionLine.h"

void OverflowScenario::apply(
    ProductionLine& line,
    int tick,
    const SimulationSettings& settings
)
{
    for(int i=0;i<3;i++)
    {
        Product p(
            9999+i,
            CakeType::CHOCOLATE
        );

        line.pushProduct(p);
    }
}

void OverflowScenario::reset(
    ProductionLine& line,
    int tick,
    const SimulationSettings& settings
)
{
}