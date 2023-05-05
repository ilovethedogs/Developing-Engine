#pragma once

namespace Developing::Graphics {
    class Viewport;
    class ScissorRect;
    class GraphicsDevice;
    class CommandQueue;
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

        //[[nodiscard]] ID3D12Device* GetDevice() const;
        //[[nodiscard]] int16_t GetNumOfBackBuffers() const;

        //[[nodiscard]] ID3D12DescriptorHeap GetDescHeap() const;

        [[nodiscard]] std::unique_ptr<SwapChain>& GetSwapChain();
        [[nodiscard]] struct ID3D12GraphicsCommandList& GetCmdList();

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
        std::unique_ptr<Fence>             p_fence;
        std::unique_ptr<SwapChain>         p_swapChain;
        std::unique_ptr<RenderTargetView>  p_RTV;
    private:
        Microsoft::WRL::ComPtr<ID3D12PipelineState> _state;
        struct D3D12_GRAPHICS_PIPELINE_STATE_DESC   _desc;
    };
}

