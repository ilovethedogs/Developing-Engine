#pragma once

namespace Growing::Graphics {
    class GraphicsDevice {
    public:
        virtual void Render();
    private:
        virtual void BeginFrame();
        virtual void EndFrame();
    private:
        std::unique_ptr<class GraphicsContext> p_context;
        std::unique_ptr<class SceneGraph> p_sceneGraph;
        std::unique_ptr<class Camera> p_camera;
    };
}

