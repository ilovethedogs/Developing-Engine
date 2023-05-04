#pragma once
#include <Core/Exception.h> 

#include <DSAL/EventQueue.h>

namespace Developing::Platform {
    class Platform {
    public:
        class WindowClass {
        public:
            WindowClass() noexcept;
            ~WindowClass();

            void Shutdown();

            WindowClass(WindowClass const&) = delete;
            WindowClass& operator=(WindowClass const&) = delete;

            [[nodiscard]] char const* GetName() const { return _name.c_str(); }
            [[nodiscard]] HINSTANCE GetInstance() const { return hInst; }
        private:
            std::string _name;
            HINSTANCE hInst;
        };
    public:
        Platform(int const width, int const height, char const* name);
        virtual ~Platform();

        std::optional<int> PumpMessage();

        [[nodiscard]] HWND GetNativeWnd() { return win32Data.hWnd; }
        [[nodiscard]] int GetWidth() const { return win32Data.width; }
        [[nodiscard]] int GetHeight() const { return win32Data.height; }

        void SetWindowSize(int width, int height);
        void SetViewportSize(int width, int height);

        void EnableCursor();
        void DisableCursor();
        void ClearKeyboard();
        void ClearMouse();

        std::optional<std::pair<int, int>> _ReadRawDelta();
    private:
        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    private:
        void ConfineCursor();
        void HideCursor();
        void FreeCursor();
        void ShowCursor();

        void EnableImGuiMouse();
        void DisableImGuiMouse();
    private:
        struct win32_data {
            int width {0};
            int height {0};
            WindowClass* wndClass;
            HWND hWnd {nullptr};
        } win32Data;

        struct RawData {
            int x;
            int y;
        };
        DSAL::EventQueue<RawData, 16u> rawDeltaBuffer;
        std::vector<BYTE> rawBuffer;
    public:
        inline static bool cursorEnabled {true};
        inline static bool rawEnabled {false};
    public:
        class HrException final : public Core::Exception {
        public:
            HrException(int line, char const* file, HRESULT hr) noexcept;
            [[nodiscard]] char const* what() const noexcept override;
            [[nodiscard]] char const* GetType() const noexcept override;
            [[nodiscard]] HRESULT GetErrorCode() const noexcept;
            [[nodiscard]] std::string GetErrorString() const noexcept;
            static std::string TranslateErrorCode(HRESULT hr) noexcept;
        private:
            HRESULT hr;
        };
    };
}

