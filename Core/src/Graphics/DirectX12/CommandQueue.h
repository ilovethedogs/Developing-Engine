#pragma once

namespace Developing::Graphics {
    class GraphicsContext;
    class SwapChain;
    class Fence;
    class CommandAllocator;

    class CommandQueue {
    public:
        CommandQueue(GraphicsContext& gfx, D3D12_COMMAND_LIST_TYPE type);
        ~CommandQueue() = default;

        [[nodiscard]] ID3D12CommandQueue* GetQueue() const { return _cmdQueue.Get(); }
    private:
        D3D12_COMMAND_LIST_TYPE _type;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> _cmdQueue;
    };
}

