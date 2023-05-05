#include "pch.h"
#include "InputHandler.h"

#include <imgui.h>

void Developing::Input::InputHandler::Init(HWND hWnd) {
    p_mouse = std::make_unique<DirectX::Mouse>();
    p_mouse->SetWindow(hWnd);

    p_kbd = std::make_unique<DirectX::Keyboard>();
}

void Developing::Input::InputHandler::ProcessMouseMsg(UINT msg, WPARAM wParam, LPARAM lParam) {
    p_mouse->ProcessMessage(msg, wParam, lParam);
}

void Developing::Input::InputHandler::ProcessKbdMsg(UINT msg, WPARAM wParam, LPARAM lParam) {
    p_kbd->ProcessMessage(msg, wParam, lParam);
}

void Developing::Input::InputHandler::EnableCursor() {
    cursorEnabled = true;
    ShowCursor();
    EnableImGuiMouse();
    FreeCursor();
}

void Developing::Input::InputHandler::DisableCursor(HWND hWnd) {
    cursorEnabled = false;
    HideCursor();
    DisableImGuiMouse();
    ConfineCursor(hWnd);
}

void Developing::Input::InputHandler::ToggleActivation(bool active, HWND hWnd) {
    if (cursorEnabled) {
        if (active) {
            ConfineCursor(hWnd); 
            HideCursor();
        }
        else {
            FreeCursor(); 
            ShowCursor();
        }
    }
}

void Developing::Input::InputHandler::ButtonDown(HWND hWnd) {
    if (!cursorEnabled) {
        ConfineCursor(hWnd);
        HideCursor();
    }
}

void Developing::Input::InputHandler::ClearKeyboard() {
    p_kbd->Reset();
}

void Developing::Input::InputHandler::ClearMouse() {
    p_mouse->ResetScrollWheelValue();
}

void Developing::Input::InputHandler::ConfineCursor(HWND hWnd) {
    RECT r;
    GetClientRect(hWnd, &r);
    MapWindowPoints(hWnd, nullptr, reinterpret_cast<POINT*>(&r), 2);
    ClipCursor(&r);
}

void Developing::Input::InputHandler::HideCursor() {
    while (::ShowCursor(FALSE) >= 0);
}

void Developing::Input::InputHandler::FreeCursor() {
    ClipCursor(nullptr);
}

void Developing::Input::InputHandler::ShowCursor() {
    while (::ShowCursor(TRUE) < 0);
}

void Developing::Input::InputHandler::EnableImGuiMouse() {
}

void Developing::Input::InputHandler::DisableImGuiMouse() {
}
