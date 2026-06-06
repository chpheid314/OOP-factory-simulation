#include "FactoryUI.h"
#include "imgui.h"

void FactoryUI::Render(const FactorySnap& snap, FactoryCmd& cmd) {
    ImGui::Begin("Cake Factory Simulator");
    DrawControls(snap, cmd);
    ImGui::Separator();
    DrawMachines(snap, cmd);
    ImGui::Separator();
    DrawInspector(snap, cmd);
    ImGui::Separator();
    DrawStats(snap);
    ImGui::Separator();
    DrawEventLog(snap, cmd);
    ImGui::End();
}

void FactoryUI::DrawControls(const FactorySnap& snap, FactoryCmd& cmd) {
    if (ImGui::Button("Start")) {
        cmd.start = true;
    } ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        cmd.pause = true;
    } ImGui::SameLine();

    if (ImGui::Button("Reset")) {
        cmd.reset = true;
    }

    ImGui::Spacing();
    ImGui::SliderFloat("Speed", &cmd.speed, 1.0f,  5.0f, "%.1fx");

    const char* scenarios[] {
        "Normal Flow",
        "Bottleneck",
        "Random Breakdowns",
        "Overflow"
    };
    int currentScenario = static_cast<int>(cmd.scenario);
    ImGui::Combo(
        "Scenario",
        &currentScenario,
        scenarios,
        IM_ARRAYSIZE(scenarios));
    cmd.scenario = static_cast<ScenarioType>(currentScenario);

    const char* cakeItems[] {
        "MATCHA",
        "CHOCOLATE",
        "STRAWBERRY"
    };
    int currentCake = static_cast<int>(cmd.recipe);
    ImGui::Combo(
        "Cake Type",
        &currentCake,
        cakeItems,
        IM_ARRAYSIZE(cakeItems));
    cmd.recipe = static_cast<CakeType>( currentCake);
    ImGui::Text("Live Tick: %d", snap.tick);
}

void FactoryUI::DrawMachines(const FactorySnap& snap, FactoryCmd& cmd)
{
    const MachineSnap* machines[] {
        &snap.sheet,
        &snap.cream,
        &snap.topping
    };

    ImGui::Text("Factory Floor");

    for (int i = 0; i < 3; i++) {
        ImGui::BeginGroup();

        bool selected =  cmd.selectedMachine == i;

        DrawMachineCard(*machines[i]);

        if (ImGui::IsItemClicked()) {
            cmd.selectedMachine = i;
        }

        if (selected) {
            ImDrawList* drawList =  ImGui::GetWindowDrawList();
            ImVec2 min = ImGui::GetItemRectMin();
            ImVec2 max =  ImGui::GetItemRectMax();
            drawList->AddRect(min, max, IM_COL32(0,255, 0, 255), 0.0f, 0, 3.0f);
        }

        ImGui::EndGroup();

        if (i < 2) {
            ImGui::SameLine();
        }
    }

    ImGui::Spacing();
    ImGui::Text("Conveyor Load");
    ImGui::ProgressBar(snap.conveyorLoad, ImVec2(400, 20));
}; 

void FactoryUI::DrawMachineCard(const MachineSnap& machine) {
    ImGui::BeginChild(machine.name.c_str(), ImVec2(180, 170), true);

    ImGui::Text("%s Machine", machine.name.c_str());

    ImGui::Separator();

    ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    const char* stateText = "UNKNOWN";

    switch (machine.state) {
    case MachineVisualState::IDLE:
        color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        stateText = "IDLE";
        break;

    case MachineVisualState::WORKING:
        color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        stateText = "WORKING";
        break;

    case MachineVisualState::BROKEN:
        color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        stateText = "BROKEN";
        break;
    }

    ImGui::Text("State:");
    ImGui::SameLine();
    ImGui::TextColored(color, "%s", stateText);
    ImGui::Text( "Health");
    ImGui::ProgressBar(machine.health, ImVec2(140, 20));
    ImGui::Text("Progress");
    ImGui::ProgressBar(machine.progress, ImVec2(140, 20));
    ImGui::EndChild();
}

void FactoryUI::DrawInspector(const FactorySnap& snap, FactoryCmd& cmd) {
    const MachineSnap* machines[] {
        &snap.sheet,
        &snap.cream,
        &snap.topping
    };

    int selected = cmd.selectedMachine;

    if (selected < 0 || selected > 2) {
        selected = 0;
    }

    const MachineSnap& machine = *machines[selected];

    ImGui::Text("Inspector");
    ImGui::Separator();

    ImGui::Text("Machine: %s", machine.name.c_str());
    ImGui::Text("Health");
    ImGui::ProgressBar(machine.health, ImVec2(200, 20));
    ImGui::Text("Queue Depth: %d", machine.queueDepth);
    ImGui::Text("Output Count: %d", machine.outputCount);
    ImGui::Text("Process Time: %.2f", machine.processTime);

    if (ImGui::Button("Force Break")) {
        cmd.forceBreak = true;
        cmd.selectedMachine = selected;
    } ImGui::SameLine();

    if (ImGui::Button("Instant Repair")) {
        cmd.instantRepair = true;
        cmd.selectedMachine = selected;
    }
}
void FactoryUI::DrawStats(const FactorySnap& snap) {
    ImGui::Text("Statistics");

    ImGui::BulletText("Finished Goods: %d", snap.finishedCount);

    ImGui::BulletText("WIP Count: %d", snap.wipCount);

    ImGui::BulletText("Breakdowns: %d", snap.breakdownCount);

    ImGui::BulletText("Lost Product: %d", snap.lostCount);
}

void FactoryUI::DrawEventLog(const FactorySnap& snap, FactoryCmd& cmd) {
    ImGui::Text("Event Log");

    if (ImGui::Button("Clear Log")) {
        cmd.clearLogs = true;
    }

    ImGui::BeginChild("LogWindow", ImVec2(0, 150), true);

    for (const auto& log : snap.logs) {
        ImGui::Text("%s", log.c_str());
    }

    ImGui::EndChild();
}

void FactoryUI::DrawConveyor(const FactorySnap& snap) {
    ImGui::Text("Conveyor");
    ImGui::ProgressBar(snap.conveyorLoad, ImVec2(200, 20));
}