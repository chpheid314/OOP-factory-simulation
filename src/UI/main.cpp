#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "FactorySnap.h"
#include "FactoryCmd.h"
#include "FactoryUI.h"
#include "UIEventListener.h"

#include "../backend/Factory.h"
#include "../backend/EventManager.h"
#include "../backend/Logger.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <cstdio>

int main(int argc, char* argv[])
{
    // Setup SDL
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                         SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Factory Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_GLContext gl_context =
        SDL_GL_CreateContext(window);

    SDL_GL_MakeCurrent(window, gl_context);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();

    //ImVec4* colors =
    //style.Colors;

    //colors[ImGuiCol_WindowBg] =
    //ImVec4(251/250.0f, 228/250.0f, 235/250.0f, 0.9f); // 배경색
    //colors[ImGuiCol_Button] =
    //ImVec4(0.70f, 0.70f, 0.70f, 1.0f); // 버튼 색상
    //colors[ImGuiCol_ButtonHovered] = 
    //ImVec4(0.80f, 0.80f, 0.80f, 1.0f); // 버튼 호버 색상
    //colors[ImGuiCol_ChildBg] = 
    //ImVec4(0.85f, 0.85f, 0.85f, 1.0f); // 자식 창 배경색

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Variables
    bool running = true;
    FactoryUI ui;
    FactorySnap snap;
    FactoryCmd cmd;
    EventManager eventBus;

    Logger::getInstance().init("app.log");

    eventBus.subscribe(&Logger::getInstance());

    UIEventListener uiListener(
        snap.logs
    );

    eventBus.subscribe(
        &uiListener
    );

    Factory factory(eventBus);

    while (running)
    {
        // Handle events
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);

            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // UI
        ui.Render(snap, cmd);

        if (cmd.start)
        {
            factory.start();
            cmd.start = false;
        }

        if (cmd.pause) 
        {
            factory.pause();
            cmd.pause = false;
        }

        if (cmd.reset)
        {
            factory.reset();
            cmd.reset = false;
        }
        
        factory.setRecipe(cmd.recipe);

        auto& scenarios = factory.getScenarioManager();

        static ScenarioType previousScenario =
            ScenarioType::NORMAL_FLOW;

        if(cmd.scenario != previousScenario)
        {
            scenarios.setEnabled(0, false);
            scenarios.setEnabled(1, false);
            scenarios.setEnabled(2, false);

            switch(cmd.scenario)
            {
            case ScenarioType::NORMAL_FLOW:
                break;

            case ScenarioType::RANDOM_BREAKDOWNS:
                scenarios.setEnabled(0, true);
                break;

            case ScenarioType::BOTTLENECK:
                scenarios.setEnabled(1, true);
                break;

            case ScenarioType::OVERFLOW:
                scenarios.setEnabled(2, true);
                break;
            }

            factory.reset();

            previousScenario =
                cmd.scenario;
        }


        auto& machines = factory.getMachines();

        if (cmd.forceBreak &&
            cmd.selectedMachine >= 0 &&
            cmd.selectedMachine < (int)machines.size())
        {
            if(
                machines[cmd.selectedMachine]
                    ->forceBreak()
            )
            {
                factory.addBreakdown();

                eventBus.emit({
                    EventType::MACHINE_BREAKDOWN,
                    machines[cmd.selectedMachine]->getName()
                        + " machine broke down (manual)"
                });
            }
            cmd.forceBreak = false;
        }

        if (cmd.instantRepair &&
            cmd.selectedMachine >= 0 &&
            cmd.selectedMachine < (int)machines.size())
        {
        if(
            machines[cmd.selectedMachine]
                ->isBroken()
        )
        {
            machines[cmd.selectedMachine]
                ->forceRepair();

            eventBus.emit({
                EventType::MACHINE_REPAIRED,
                machines[cmd.selectedMachine]->getName()
                + " machine repaired (manual)"
            });
        }
        cmd.instantRepair = false;
        }

// =========================
// Backend Update
// =========================

        factory.update();

// =========================
// Backend -> Snap
// =========================

        snap.tick = factory.getTick();

        snap.running = factory.isRunning();

        snap.finishedCount = factory.getFinishedCount();

        snap.lostCount = factory.getLostCount();

        snap.breakdownCount = factory.getBreakdownCount();

        snap.recipe = factory.getRecipe();

        snap.wipCount = factory.getWipCount();

// =========================
// Machine Snapshot
// =========================

        if (machines.size() >= 3)
        {
            snap.sheet.name =
                machines[0]->getName();

            snap.sheet.health =
                machines[0]->getHealth()/100.0f;

            if (machines[0]->getState() == "BROKEN")
            {
                snap.sheet.state =
                    MachineVisualState::BROKEN;
            }
            else if (machines[0]->getState() == "WORKING")
            {
                snap.sheet.state =
                    MachineVisualState::WORKING;
            }
            else
            {
                snap.sheet.state =
                    MachineVisualState::IDLE;
            }

            snap.sheet.progress =
                machines[0]->getProgress()/100.0f;

            snap.sheet.queueDepth =
                machines[0]->getQueueSize();

            snap.sheet.outputCount =
                machines[0]->getOutputCount();

            snap.cream.name =
                machines[1]->getName();

            snap.cream.health =
                machines[1]->getHealth() / 100.0f;

            if (machines[1]->getState() == "BROKEN")
            {
                snap.cream.state =
                    MachineVisualState::BROKEN;
            }
            else if (machines[1]->getState() == "WORKING")
            {
                snap.cream.state =
                    MachineVisualState::WORKING;
            }
            else
            {
                snap.cream.state =
                    MachineVisualState::IDLE;
            }

            snap.cream.progress =
                machines[1]->getProgress() / 100.0f;

            snap.cream.queueDepth =
                machines[1]->getQueueSize();

            snap.cream.outputCount =
                machines[1]->getOutputCount();

            snap.topping.name =
                machines[2]->getName();

            snap.topping.health =
                machines[2]->getHealth() / 100.0f;

            if (machines[2]->getState() == "BROKEN")
            {
                snap.topping.state =
                    MachineVisualState::BROKEN;
            }
            else if (machines[2]->getState() == "WORKING")
            {
                snap.topping.state =
                    MachineVisualState::WORKING;
            }
            else
            {
                snap.topping.state =
                    MachineVisualState::IDLE;
            }

            snap.topping.progress =
                machines[2]->getProgress() / 100.0f;

            snap.topping.queueDepth =
                machines[2]->getQueueSize();

            snap.topping.outputCount =
                machines[2]->getOutputCount();
            bool overflowEnabled =
                cmd.scenario ==
                ScenarioType::OVERFLOW;

            snap.sheet.finiteQueue =
                overflowEnabled;

            snap.cream.finiteQueue =
                overflowEnabled;

            snap.topping.finiteQueue =
                overflowEnabled;

            if (overflowEnabled)
            {
                snap.sheet.conveyorLoad =
                    machines[0]->getQueueSize() / 10.0f;

                snap.cream.conveyorLoad =
                    machines[1]->getQueueSize() / 10.0f;

                snap.topping.conveyorLoad =
                    machines[2]->getQueueSize() / 10.0f;
            }
            else
            {
                snap.sheet.conveyorLoad = 0.0f;
                snap.cream.conveyorLoad = 0.0f;
                snap.topping.conveyorLoad = 0.0f;
            }
        }

        if (cmd.clearLogs)
        {
        snap.logs.clear();
        cmd.clearLogs = false;
        }
        // Input
        //ImGui::End();

        // Render
        ImGui::Render();

        glViewport(0, 0, 1280, 720);
        glClearColor(251/250.0f, 228/250.0f, 235/250.0f, 0.9f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );

        SDL_GL_SwapWindow(window);

        int delay = 200 / cmd.speed;

        if (delay < 10)
        {
            delay = 10;
        }

        SDL_Delay(delay);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}