#pragma once

namespace Developing::Graphics {
    class GraphicsDevice;
    class CommandQueue;
    struct WindowData;

    class SwapChain {
    public:
        SwapChain(std::unique_ptr<GraphicsDevice>& p_device, std::unique_ptr<CommandQueue>& p_cmdQueue, WindowData const& info);
        ~SwapChain() = default;

        void Present();
        void Swap();

        [[nodiscard]] IDXGISwapChain* GetSwapChain() const { return _swapChain.Get(); }
        [[nodiscard]] ID3D12Resource* GetRenderTargets() const { return _renderTarget[0].Get(); }
        ID3D12Resource* GetRenderTargetAt(uint16_t i) const { return _renderTarget[i].Get(); }
        [[nodiscard]] ID3D12Resource* GetCurrentRenderTarget() const { return _renderTarget[_bufferIdx].Get(); }
        
        [[nodiscard]] uint16_t GetCurrentBufferIndex() const { return _bufferIdx; }
        [[nodiscard]] uint16_t GetNumOfBuffers() const { return NUM_BACK_BUFFERS; }
    public:
        static constexpr uint16_t NUM_BACK_BUFFERS {3};
        Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
        Microsoft::WRL::ComPtr<ID3D12Resource> _renderTarget[NUM_BACK_BUFFERS];
        uint16_t                               _bufferIdx {};
    };
}

