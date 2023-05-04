#include "pch.h"
#include "Fence.h"

#include "CommandQueue.h"
#include "Graphics/DirectX12/GraphicsDevice.h"

Developing::Graphics::Fence::Fence(GraphicsDevice& _device) {
    _device.GetDevice()->CreateFence(0u, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(_fence.ReleaseAndGetAddressOf()));
    _fenceHandle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

Developing::Graphics::Fence::~Fence() {
    ::CloseHandle(_fenceHandle);
}

void Developing::Graphics::Fence::SetSignal(CommandQueue& _cmdQueue) {
    _cmdQueue.GetCmdQueue()->Signal(_fence.Get(), _fenceValue);
}

void Developing::Graphics::Fence::SetSignalNext(CommandQueue& _cmdQueue) {
    ++_fenceValue;
    SetSignal(_cmdQueue);
}

void Developing::Graphics::Fence::Wait() {
    if (_fence->GetCompletedValue() < _fenceValue) {
        _fence->SetEventOnCompletion(_fenceValue, _fenceHandle);
        ::WaitForSingleObject(_fenceHandle, INFINITE);
    }
}
