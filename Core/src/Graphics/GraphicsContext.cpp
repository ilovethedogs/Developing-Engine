#include "pch.h"
#include "GraphicsContext.h"

#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/CommandQueue.h"
#include "Graphics/DirectX12/Fence.h"
#include "Graphics/DirectX12/SwapChain.h"
#include "Graphics/DirectX12/Bindable/DescHeap/RenderTargetView.h"
#include "Graphics/DirectX12/Bindable/Viewport.h"
#include "Graphics/DirectX12/Bindable/ScissorRect.h"

Developing::Graphics::GraphicsContext::GraphicsContext(int width, int height, HWND nativeWnd, bool windowed)
    : _windowData{width, height, nativeWnd, windowed}
{
    p_device = std::make_unique<GraphicsDevice>();
    p_cmdQueue = std::make_unique<CommandQueue>(p_device);
    p_fence = std::make_unique<Fence>(p_device);
    p_swapChain = std::make_unique<SwapChain>(p_device, p_cmdQueue, _windowData);
    p_RTV = std::make_unique<RenderTargetView>(p_device, p_swapChain, 3);

    p_vp = std::make_unique<Viewport>(width, height);
    p_rect = std::make_unique<ScissorRect>(0, 0, width, height);
}

Developing::Graphics::GraphicsContext::~GraphicsContext() {
}

std::unique_ptr<Developing::Graphics::SwapChain>& Developing::Graphics::GraphicsContext::GetSwapChain() {
    return p_swapChain;
}

ID3D12GraphicsCommandList& Developing::Graphics::GraphicsContext::GetCmdList() {
    return *p_cmdQueue->_cmdList.Get();
}

void Developing::Graphics::GraphicsContext::Render() {
    BeginFrame();
    EndFrame();
}

void Developing::Graphics::GraphicsContext::BeginFrame() {
    p_cmdQueue->_cmdAllocator->Reset();
    p_cmdQueue->_cmdList->Reset(p_cmdQueue->_cmdAllocator.Get(), nullptr);

    D3D12_RESOURCE_BARRIER barrier {
        CD3DX12_RESOURCE_BARRIER::Transition(
            p_swapChain->GetCurrentRenderTarget(),
            D3D12_RESOURCE_STATE_PRESENT,
            D3D12_RESOURCE_STATE_RENDER_TARGET
        )
    };

    p_cmdQueue->_cmdList->ResourceBarrier(1u, &barrier);

    p_vp->Bind(*this);
    p_rect->Bind(*this);

    ClearScreen();
}

void Developing::Graphics::GraphicsContext::EndFrame() {
    D3D12_RESOURCE_BARRIER barrier {
        CD3DX12_RESOURCE_BARRIER::Transition(
            p_swapChain->GetCurrentRenderTarget(),
            D3D12_RESOURCE_STATE_RENDER_TARGET,
            D3D12_RESOURCE_STATE_PRESENT
        )
    };

    p_cmdQueue->_cmdList->ResourceBarrier(1u, &barrier);
    p_cmdQueue->_cmdList->Close();

    ExecuteCommand();
}

void Developing::Graphics::GraphicsContext::ExecuteCommand() {
    ID3D12CommandList* cmdList[] {p_cmdQueue->_cmdList.Get()};
    p_cmdQueue->_cmdQueue->ExecuteCommandLists(_countof(cmdList), cmdList);

    p_swapChain->Present();

    p_fence->SetSignalNext(p_cmdQueue);
    p_fence->Wait();

    p_swapChain->Swap();
}

void Developing::Graphics::GraphicsContext::ClearScreen() {
    p_RTV->Clear(*this);
    p_RTV->Bind(*this);
}
