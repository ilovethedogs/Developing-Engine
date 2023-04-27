#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Growing::Core {
    class Log {
    public:
        static void Init();
        static void Shutdown();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger> GetGUILogger() { return s_GUILogger; }
        static std::shared_ptr<spdlog::logger> GetGraphicsLogger() { return s_GraphicsLogger; }

        static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
    private:
        inline static std::shared_ptr<spdlog::logger> s_CoreLogger {nullptr};
        inline static std::shared_ptr<spdlog::logger> s_GUILogger {nullptr};
        inline static std::shared_ptr<spdlog::logger> s_GraphicsLogger {nullptr};

        inline static std::shared_ptr<spdlog::logger> s_ClientLogger {nullptr};
    };
}

// Core log macros
#define CORE_TRACE(...)          ::Growing::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)           ::Growing::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)           ::Growing::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)          ::Growing::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...)          ::Growing::Core::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// GUI log macros
#define GUI_TRACE(...)           ::Growing::Core::Log::GetGUILogger()->trace(__VA_ARGS__)
#define GUI_INFO(...)            ::Growing::Core::Log::GetGUILogger()->info(__VA_ARGS__)
#define GUI_WARN(...)            ::Growing::Core::Log::GetGUILogger()->warn(__VA_ARGS__)
#define GUI_ERROR(...)           ::Growing::Core::Log::GetGUILogger()->error(__VA_ARGS__)
#define GUI_FATAL(...)           ::Growing::Core::Log::GetGUILogger()->fatal(__VA_ARGS__)

// Graphics log macros
#define GRAPHICS_TRACE(...)      ::Growing::Core::Log::GetGraphicsLogger()->trace(__VA_ARGS__)
#define GRAPHICS_INFO(...)       ::Growing::Core::Log::GetGraphicsLogger()->info(__VA_ARGS__)
#define GRAPHICS_WARN(...)       ::Growing::Core::Log::GetGraphicsLogger()->warn(__VA_ARGS__)
#define GRAPHICS_ERROR(...)      ::Growing::Core::Log::GetGraphicsLogger()->error(__VA_ARGS__)
#define GRAPHICS_FATAL(...)      ::Growing::Core::Log::GetGraphicsLogger()->fatal(__VA_ARGS__)

// Throw Exception
#ifdef GW_PLATFORM_WINDOWS
#define WND_EXCEPT(hr) PlatformWin32::HrException(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() PlatformWin32::HrException(__LINE__,__FILE__,GetLastError())
#endif
