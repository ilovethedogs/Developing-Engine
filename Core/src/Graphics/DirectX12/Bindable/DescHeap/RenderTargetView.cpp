#include "pch.h"
#include "RenderTargetView.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/SwapChain.h"

#include <DirectXColors.h>

Developing::Graphics::RenderTargetView::RenderTargetView(std::unique_ptr<GraphicsDevice> const& p_device, std::unique_ptr<SwapChain> const& p_swapChain, uint16_t num)
    : DescriptorHeap{num}
{
    D3D12_DESCRIPTOR_HEAP_DESC desc;
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    desc.NumDescriptors = _num;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    desc.NodeMask = 0;

    _handle.resize(_num);
    _heapSize = p_device->GetDevice()->GetDescriptorHandleIncrementSize(desc.Type);
    p_device->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(_descHeap.ReleaseAndGetAddressOf()));

    D3D12_CPU_DESCRIPTOR_HANDLE const heap_begin {_descHeap->GetCPUDescriptorHandleForHeapStart()};
    for (auto i {0}; i != _num; ++i) {
        _handle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(heap_begin, i * _heapSize);
        p_device->GetDevice()->CreateRenderTargetView(p_swapChain->GetRenderTargetAt(i), nullptr, _handle[i]);
    }
}

Developing::Graphics::RenderTargetView::~RenderTargetView() {
}

void Developing::Graphics::RenderTargetView::Clear(GraphicsContext& gfx) noexcept {
    gfx.GetCmdList().ClearRenderTargetView(
        GetHandle(gfx.GetSwapChain()->GetCurrentBufferIndex()), 
        DirectX::Colors::PapayaWhip, 
        0, 
        nullptr);
}

void Developing::Graphics::RenderTargetView::Bind(GraphicsContext& gfx) noexcept {
    auto const backbuf {GetHandle(gfx.GetSwapChain()->GetCurrentBufferIndex())};
    gfx.GetCmdList().OMSetRenderTargets(
        1u, 
        &backbuf,
        FALSE, 
        nullptr
    );
}

std::string Developing::Graphics::RenderTargetView::GetUID() const noexcept {
    return "";
}
