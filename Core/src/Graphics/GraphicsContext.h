#pragma once

namespace Developing::Graphics {
    class Viewport;
    class ScissorRect;
    class GraphicsDevice;
    class CommandQueue;
    class CommandAllocator;
    class CommandList;
    class Fence;
    class RenderTargetView;
    class SwapChain;

    struct WindowData {
        int width;
        int height;
        HWND nativeWnd;
        bool windowed;
    };
    
    class GraphicsContext {
    public:
        GraphicsContext(int width, int height, HWND nativeWnd, bool windowed);
        ~GraphicsContext();

        [[nodiscard]] std::unique_ptr<GraphicsDevice>& GetDeviceImpl();
        [[nodiscard]] std::unique_ptr<CommandQueue>& GetCommandQueueImpl();
        [[nodiscard]] std::unique_ptr<SwapChain>& GetSwapChainImpl();
        //[[nodiscard]] struct ID3D12GraphicsCommandList& GetCmdList();

        [[nodiscard]] WindowData& GetWindowData();

        void Render();
    private:
        void BeginFrame();
        void EndFrame();
        void ExecuteCommand();
        void ClearScreen();
    private:
        std::unique_ptr<Viewport> p_vp;
        std::unique_ptr<ScissorRect> p_rect;
    private:
        WindowData _windowData;
    private:
        std::unique_ptr<GraphicsDevice>    p_device;
        std::unique_ptr<CommandQueue>      p_cmdQueue;
        std::unique_ptr<CommandAllocator>  p_cmdAllocator;
        std::unique_ptr<CommandList>       p_cmdList;
        std::unique_ptr<Fence>             p_fence;
        std::unique_ptr<SwapChain>         p_swapChain;
        std::unique_ptr<RenderTargetView>  p_RTV;
    };
}

