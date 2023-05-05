#pragma once

#include <directxtk12/Mouse.h>
#include <directxtk12/Keyboard.h>

namespace Developing::Input {
    class InputHandler {
    public:
        static void Init(HWND hWnd); 

        [[nodiscard]] static bool IsCursorEnabled() { return cursorEnabled; }

        static void ProcessMouseMsg(UINT msg, WPARAM wParam, LPARAM lParam);
        static void ProcessKbdMsg(UINT msg, WPARAM wParam, LPARAM lParam);

        static void EnableCursor();
        static void DisableCursor(HWND hWnd);

        static void ToggleActivation(bool active, HWND hWnd);
        static void ButtonDown(HWND hWnd);

        static void ClearKeyboard();
        static void ClearMouse();
    private:
        static void ConfineCursor(HWND hWnd);
        static void HideCursor();
        static void FreeCursor();
        static void ShowCursor();
        static void EnableImGuiMouse();
        static void DisableImGuiMouse();
    private:
        inline static bool cursorEnabled {true};
        inline static std::unique_ptr<DirectX::Mouse> p_mouse;
        inline static std::unique_ptr<DirectX::Keyboard> p_kbd;
    };
}
