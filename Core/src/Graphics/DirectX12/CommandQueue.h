#pragma once

#include <d3d12.h>

namespace Developing::Graphics {
    class GraphicsDevice;
    class SwapChain;
    class Fence;

    class CommandQueue {
    public:
        CommandQueue(std::unique_ptr<GraphicsDevice> const& p_device);
        ~CommandQueue() = default;

        [[nodiscard]] ID3D12CommandQueue* GetCmdQueue() const { return _cmdQueue.Get(); }

        void BeginFrame(SwapChain& _swapChain, D3D12_VIEWPORT const& vp, D3D12_RECT const& rect);
        void EndFrame();
        void WaitSync();
    private:
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>        _cmdQueue;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>    _cmdAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _cmdList;
    };
}

