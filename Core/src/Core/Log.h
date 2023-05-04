#pragma once

#include <Core/Core.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Developing::Core {
    class Log {
    public:
        static void Init();
        static void Shutdown();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger> GetGUILogger() { return s_GUILogger; }
        static std::shared_ptr<spdlog::logger> GetGraphicsLogger() { return s_GraphicsLogger; }
        static std::shared_ptr<spdlog::logger> GetPlatformLogger() { return s_PlatformLogger; }

        static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
    private:
        inline static std::shared_ptr<spdlog::logger> s_CoreLogger {nullptr};
        inline static std::shared_ptr<spdlog::logger> s_GUILogger {nullptr};
        inline static std::shared_ptr<spdlog::logger> s_GraphicsLogger {nullptr};
        inline static std::shared_ptr<spdlog::logger> s_PlatformLogger {nullptr};

        inline static std::shared_ptr<spdlog::logger> s_ClientLogger {nullptr};
    };
}

// Core log macros
#define CORE_TRACE(...)          ::Developing::Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...)           ::Developing::Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...)           ::Developing::Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...)          ::Developing::Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_FATAL(...)          ::Developing::Core::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// GUI log macros
#define GUI_TRACE(...)           ::Developing::Core::Log::GetGUILogger()->trace(__VA_ARGS__)
#define GUI_INFO(...)            ::Developing::Core::Log::GetGUILogger()->info(__VA_ARGS__)
#define GUI_WARN(...)            ::Developing::Core::Log::GetGUILogger()->warn(__VA_ARGS__)
#define GUI_ERROR(...)           ::Developing::Core::Log::GetGUILogger()->error(__VA_ARGS__)
#define GUI_FATAL(...)           ::Developing::Core::Log::GetGUILogger()->fatal(__VA_ARGS__)

// Graphics log macros
#define GRAPHICS_TRACE(...)      ::Developing::Core::Log::GetGraphicsLogger()->trace(__VA_ARGS__)
#define GRAPHICS_INFO(...)       ::Developing::Core::Log::GetGraphicsLogger()->info(__VA_ARGS__)
#define GRAPHICS_WARN(...)       ::Developing::Core::Log::GetGraphicsLogger()->warn(__VA_ARGS__)
#define GRAPHICS_ERROR(...)      ::Developing::Core::Log::GetGraphicsLogger()->error(__VA_ARGS__)
#define GRAPHICS_FATAL(...)      ::Developing::Core::Log::GetGraphicsLogger()->fatal(__VA_ARGS__)

// Platform log macros
#define PLATFORM_TRACE(...)      ::Developing::Core::Log::GetPlatformLogger()->trace(__VA_ARGS__)
#define PLATFORM_INFO(...)       ::Developing::Core::Log::GetPlatformLogger()->info(__VA_ARGS__)
#define PLATFORM_WARN(...)       ::Developing::Core::Log::GetPlatformLogger()->warn(__VA_ARGS__)
#define PLATFORM_ERROR(...)      ::Developing::Core::Log::GetPlatformLogger()->error(__VA_ARGS__)
#define PLATFORM_FATAL(...)      ::Developing::Core::Log::GetPlatformLogger()->fatal(__VA_ARGS__)

// Throw Exception
#ifdef GW_PLATFORM_WINDOWS
#define WND_EXCEPT(hr) PlatformWin32::HrException(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() PlatformWin32::HrException(__LINE__,__FILE__,GetLastError())
#endif
