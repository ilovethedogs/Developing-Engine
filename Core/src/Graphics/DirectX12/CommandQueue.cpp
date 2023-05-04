#include "pch.h"
#include "CommandQueue.h"

#include "SwapChain.h"
#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/Fence.h"

Developing::Graphics::CommandQueue::CommandQueue(std::unique_ptr<GraphicsDevice> const& p_device) {
    D3D12_COMMAND_QUEUE_DESC qd {};
    qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    qd.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    p_device->GetDevice()->CreateCommandQueue(&qd, IID_PPV_ARGS(_cmdQueue.ReleaseAndGetAddressOf()));
    p_device->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(_cmdAllocator.ReleaseAndGetAddressOf()));
    p_device->GetDevice()->CreateCommandList(0u, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAllocator.Get(), nullptr, IID_PPV_ARGS(_cmdList.ReleaseAndGetAddressOf()));

    _cmdList->Close();
}

void Developing::Graphics::CommandQueue::BeginFrame(SwapChain& _swapChain, D3D12_VIEWPORT const& vp, D3D12_RECT const& rect) {
}

void Developing::Graphics::CommandQueue::EndFrame() {
}

void Developing::Graphics::CommandQueue::WaitSync() {
}
