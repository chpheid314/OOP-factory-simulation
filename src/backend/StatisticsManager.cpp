#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
    reset();
}

void StatisticsManager::reset()
{
    finishedCount = 0;
    lostCount = 0;
    breakdownCount = 0;
}

void StatisticsManager::addFinished()
{
    ++finishedCount;
}

void StatisticsManager::addLost()
{
    ++lostCount;
}

void StatisticsManager::addBreakdown()
{
    ++breakdownCount;
}

int StatisticsManager::getFinishedCount() const
{
    return finishedCount;
}

// TODO:
 // Increase lost count when product is discarded

// TODO:
 // Increase breakdown count when machine enters broken state

int StatisticsManager::getLostCount() const
{
    return lostCount;
}

int StatisticsManager::getBreakdownCount() const
{
    return breakdownCount;
}