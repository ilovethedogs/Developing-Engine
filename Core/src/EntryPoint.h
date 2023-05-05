#pragma once

int main(int argc, char* argv[]) {
    Developing::Core::Log::Init();
    CORE_INFO("Log Initialized");

    auto app {Developing::Core::CreateApp()};
    auto const result {app->Run()};
    delete app;
    app = nullptr;

    Developing::Core::Log::Shutdown();

    return result;
}
