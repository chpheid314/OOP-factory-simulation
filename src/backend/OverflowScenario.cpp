#include "OverflowScenario.h"

#include "ProductionLine.h"

void OverflowScenario::apply(
    ProductionLine& line
)
{
    line.setOverflowMode(true);
}

void OverflowScenario::reset(
    ProductionLine& line
)
{
    line.setOverflowMode(false);
}