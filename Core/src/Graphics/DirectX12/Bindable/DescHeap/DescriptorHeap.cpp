#include "pch.h"
#include "DescriptorHeap.h"

#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/SwapChain.h"

Developing::Graphics::DescriptorHeap::DescriptorHeap(uint16_t num)
    : Bindable{}, _num{num}
{
}

Developing::Graphics::DescriptorHeap::~DescriptorHeap() {
}

D3D12_CPU_DESCRIPTOR_HANDLE Developing::Graphics::DescriptorHeap::GetHandle(int16_t idx) const {
    CORE_ASSERT(idx < _num, "");
    return _handle[idx];
}

