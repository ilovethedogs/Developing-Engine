#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Growing::Core {
    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("Core");
        s_CoreLogger->set_level(spdlog::level::level_enum::trace);

        s_GUILogger = spdlog::stdout_color_mt("GUI");
        s_GUILogger->set_level(spdlog::level::level_enum::trace);

        s_GraphicsLogger = spdlog::stdout_color_mt("Graphics");
        s_GraphicsLogger->set_level(spdlog::level::level_enum::trace);

        s_ClientLogger = spdlog::stdout_color_mt("Client");
        s_ClientLogger->set_level(spdlog::level::level_enum::trace);
    }

    void Log::Shutdown() {
        CORE_INFO("Shutting down Logger!");
    }   
}