#pragma once

class StatisticsManager
{
private:
    int finishedCount;
    int lostCount;
    int breakdownCount;

public:
    StatisticsManager();

    void reset();

    void addFinished();
    void addLost();
    void addBreakdown();

    int getFinishedCount() const;
    int getLostCount() const;
    int getBreakdownCount() const;
};