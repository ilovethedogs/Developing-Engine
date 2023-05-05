#include "pch.h"
#include "Fence.h"

#include "CommandQueue.h"
#include "Graphics/DirectX12/GraphicsDevice.h"

Developing::Graphics::Fence::Fence(std::unique_ptr<GraphicsDevice> const& p_device) {
    p_device->GetDevice()->CreateFence(0u, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
    _fenceHandle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

Developing::Graphics::Fence::~Fence() {
    ::CloseHandle(_fenceHandle);
}

void Developing::Graphics::Fence::SetSignal(std::unique_ptr<CommandQueue> const& p_cmdQueue) {
    p_cmdQueue->GetCmdQueue()->Signal(_fence.Get(), _fenceValue);
}

void Developing::Graphics::Fence::SetSignalNext(std::unique_ptr<CommandQueue> const& p_cmdQueue) {
    ++_fenceValue;
    SetSignal(p_cmdQueue);
}

void Developing::Graphics::Fence::Wait() {
    if (_fence->GetCompletedValue() < _fenceValue) {
        _fence->SetEventOnCompletion(_fenceValue, _fenceHandle);
        ::WaitForSingleObject(_fenceHandle, INFINITE);
    }
}
