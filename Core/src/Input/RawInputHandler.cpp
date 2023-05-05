#include "pch.h"
#include "RawInputHandler.h"

void Developing::Input::RawInputHandler::Init() {
    RAWINPUTDEVICE rid;
    rid.usUsagePage = 0x01;
    rid.usUsage     = 0x02;
    rid.dwFlags     = 0;
    rid.hwndTarget  = nullptr;
    CORE_ASSERT(RegisterRawInputDevices(&rid, 1, sizeof(rid)), "raw device init failed!");

    rawEnabled = true;
}

void Developing::Input::RawInputHandler::ProcessRawInput(UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!rawEnabled)
        return;

    UINT size;
    // first get the size of the input data
    if (GetRawInputData(
        reinterpret_cast<HRAWINPUT>(lParam),
        RID_INPUT,
        nullptr,
        &size,
        sizeof(RAWINPUTHEADER)) == -1) 
    {
        return;     
    }
    rawBuffer.resize(size);
    if (GetRawInputData(
        reinterpret_cast<HRAWINPUT>(lParam),
        RID_INPUT,
        rawBuffer.data(),
        &size,
        sizeof(RAWINPUTHEADER)) == -1) 
    {
        return;     
    }

    // process the data
    auto& ri {reinterpret_cast<RAWINPUT const&>(*rawBuffer.data())};
    if (ri.header.dwType == RIM_TYPEMOUSE && ri.data.mouse.lLastX != 0 || ri.data.mouse.lLastY)
        rawDeltaBuffer.push<RawData>(ri.data.mouse.lLastX, ri.data.mouse.lLastY);
}

std::optional<std::pair<int, int>> Developing::Input::RawInputHandler::ReadRawDelta() {
    if (rawDeltaBuffer.empty()) [[unlikely]]
        return std::nullopt;
    auto const d {rawDeltaBuffer.front()};
    rawDeltaBuffer.pop();
    return std::pair{d.x, d.y};
}
