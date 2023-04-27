#pragma once

namespace Growing::GUI {
    class ImGuiMan {
    public:
        ImGuiMan();
        ~ImGuiMan();

        void BeginFrame();
        void EndFrame();
    };
}

