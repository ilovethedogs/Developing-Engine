#pragma once

namespace Developing::Graphics {
    class GraphicsDevice;
    class CommandQueue;
    class Fence;
    class DescriptorHeap;
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

        //[[nodiscard]] ID3D12Device* GetDevice() const;
        //[[nodiscard]] int16_t GetNumOfBackBuffers() const;

        //[[nodiscard]] ID3D12DescriptorHeap GetDescHeap() const;

        void Render();
    private:
        void BeginFrame();
        void EndFrame();
        void ExecuteCommand();
        void ClearScreen();
    private:
        std::unique_ptr<struct D3D12_VIEWPORT> vp;
        std::unique_ptr<struct CD3DX12_RECT> rect;
    private:
        WindowData _windowData;
    private:
        std::unique_ptr<GraphicsDevice>  p_device;
        std::unique_ptr<CommandQueue>    p_cmdQueue;
        std::unique_ptr<Fence>           p_fence;
        std::unique_ptr<SwapChain>       p_swapChain;
        std::unique_ptr<DescriptorHeap>  p_RTV;
    };
}

