#include "pch.h"
#include "DescriptorHeap.h"

#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/SwapChain.h"

Developing::Graphics::DescriptorHeap::DescriptorHeap(DescHeapType Type, std::unique_ptr<GraphicsDevice> const& p_device, std::unique_ptr<SwapChain> const& p_swapChain, uint16_t num)
    : _num{num}
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.Type = GetType(Type);
    desc.NumDescriptors = _num;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    desc.NodeMask = 0;

    _handle.resize(_num);
    _heapSize = p_device->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type);
    p_device->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(_descHeap.ReleaseAndGetAddressOf()));

    D3D12_CPU_DESCRIPTOR_HANDLE const heap_begin {_descHeap->GetCPUDescriptorHandleForHeapStart()};
    for (auto i {0}; i != _num; ++i) {
        _handle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(heap_begin, i * _heapSize);
        switch (Type) {
        case DescHeapType::RenderTargetView:
            CREATE(p_device->GetDevice(), RenderTargetView, p_swapChain->GetRenderTargetAt(i), nullptr, _handle[i]);
            break;
        case DescHeapType::DepthStencilView: break;
        case DescHeapType::ConstantBufferView: break;
        case DescHeapType::ShaderResourceView: break;
        case DescHeapType::UnorderedAccessView: break;
        default: ;
        }
    }
}

D3D12_CPU_DESCRIPTOR_HANDLE Developing::Graphics::DescriptorHeap::GetHandle(int16_t idx) const {
    CORE_ASSERT(idx < _num, "");
    return _handle[idx];
}

