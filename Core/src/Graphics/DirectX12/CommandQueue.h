#pragma once

namespace Developing::Graphics {
    class GraphicsDevice;
    class SwapChain;
    class Fence;

    class CommandQueue {
    public:
        CommandQueue(std::unique_ptr<GraphicsDevice> const& p_device);
        ~CommandQueue() = default;

        [[nodiscard]] ID3D12CommandQueue* GetCmdQueue() const { return _cmdQueue.Get(); }

        void ClearQueue();
        void SetResourceBarriers(UINT num_barriers, D3D12_RESOURCE_BARRIER const* p_barriers);
        void SetViewPorts(UINT num_viewports, D3D12_VIEWPORT const* p_viewports);
        void SetScissorRects(UINT num_rects, D3D12_RECT const* p_rects);
    public:
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>        _cmdQueue;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>    _cmdAllocator;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _cmdList;
    };
}

