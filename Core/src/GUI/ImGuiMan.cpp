#include "pch.h"
#include "ImGuiMan.h"

#include <imgui.h>

#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

namespace Growing::GUI {
    ImGuiMan::ImGuiMan() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(Platform::GetNativeWnd());
        ImGui_ImplDX11_Init(
            static_cast<ID3D11Device*>(RenderContext::GetImplDevice()), 
            static_cast<ID3D11DeviceContext*>(RenderContext::GetImplContext())
        );
    }

    ImGuiMan::~ImGuiMan() {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiMan::BeginFrame() {
    }

    void ImGuiMan::EndFrame() {
    }
}
