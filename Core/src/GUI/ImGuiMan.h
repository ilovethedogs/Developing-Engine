#pragma once

namespace Developing::Platform {
    class Platform;
}

namespace Developing::Graphics {
    class GraphicsContext;
}

namespace Developing::GUI {
    class ImGuiMan {
    public:
        ImGuiMan(Platform::Platform& platform, Graphics::GraphicsContext& gfx);
        ~ImGuiMan();

        void BeginFrame();
        void EndFrame();

        static bool IsImguiEnabled() { return imguiEnabled; }
    private:
        inline static bool imguiEnabled {false};
    };
}

