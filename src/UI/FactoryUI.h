#pragma once

#include "FactorySnap.h"
#include "FactoryCmd.h"

class FactoryUI
{
public:
    void Render(const FactorySnap& snap, FactoryCmd& cmd);

private:
    int selectedMachine = 0;

    void DrawControls(const FactorySnap& snap, FactoryCmd& cmd);

    void DrawMachines(const FactorySnap& snap, FactoryCmd& cmd);

    void DrawMachineCard(const MachineSnap& machine);

    void DrawInspector( const FactorySnap& snap,FactoryCmd& cmd);

    void DrawStats(const FactorySnap& snap);

    void DrawEventLog(const FactorySnap& snap, FactoryCmd& cmd);

    void DrawConveyor(const FactorySnap& snap);
};