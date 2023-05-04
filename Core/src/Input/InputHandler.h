#pragma once

namespace Developing::Input {
    class InputHandler {
    public:
        [[nodiscard]] static bool CursorEnabled();

        [[nodiscard]] static std::optional<std::pair<int, int>> ReadRawDelta();

        void ClearKeyboard();
        void ClearMouse();
    };
}
