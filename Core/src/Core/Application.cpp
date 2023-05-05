#include "pch.h"
#include "Application.h"

#include "Platform/Platform.h"
#include "Graphics/GraphicsContext.h"

Developing::Core::Application::Application() {
    width = 1600;
    height = 900;
    p_platform = std::make_unique<Platform::Platform>(width, height);
    p_gfx = std::make_unique<Graphics::GraphicsContext>(width, height, p_platform->GetNativeWnd(), true);
}

Developing::Core::Application::~Application() {
}

int Developing::Core::Application::Run() {
    while (true) {
        if (auto const ecode {p_platform->PumpMessage()}; ecode.has_value()) [[unlikely]]
            return *ecode;

        ProcessInput();
        Update(1.0f);
        Render();
    }
}

void Developing::Core::Application::ProcessInput() {
}

void Developing::Core::Application::Update(float const dt) {
}

void Developing::Core::Application::Render() {
    p_gfx->Render();
}
