#pragma once

namespace Developing::Input {
    class RawInput {
    public:
        RawInput();

        void EnableCursor();
        void DisableCursor();
        void EnableRaw();
        void DisableRaw();
    };
}

