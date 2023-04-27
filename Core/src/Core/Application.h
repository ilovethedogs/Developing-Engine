#pragma once

namespace Growing {
    namespace Platform {
        class Platform;
    }

    namespace GUI {
        class ImGuiMan;
    }

    namespace Graphics {
        class GraphicsDevice;
    }
}

namespace Growing::Core {
    class Application {
    public:
        Application();
        virtual ~Application();

        Application(Application const&) = delete;
        Application& operator=(Application const&) = delete;

        int Run();
    protected:
    };
}

