#pragma once

#include <DSAL/EventQueue.h>

namespace Developing::Input {
    struct RawData {
        int x;
        int y;
    };

    class RawInputHandler {
    public:
        static void Init();

        static void ProcessRawInput(UINT msg, WPARAM wParam, LPARAM lParam);

        [[nodiscard]] static std::optional<std::pair<int, int>> ReadRawDelta();

        static void EnableRaw() { rawEnabled = true; };
        static void DisableRaw() { rawEnabled = false; };

        static bool IsRawEnabled() { return rawEnabled; }
    private:
        inline static DSAL::EventQueue<RawData, 16u> rawDeltaBuffer;
        inline static std::vector<BYTE> rawBuffer;
        inline static bool rawEnabled {false};
    };
}

