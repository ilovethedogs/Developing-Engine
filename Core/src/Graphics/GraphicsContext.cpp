#include "pch.h"
#include "GraphicsContext.h"

#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/CommandQueue.h"
#include "Graphics/DirectX12/Fence.h"
#include "Graphics/DirectX12/SwapChain.h"
#include "Graphics/DirectX12/DescriptorHeap.h"

#include <DirectXColors.h>

Developing::Graphics::GraphicsContext::GraphicsContext(int width, int height, HWND nativeWnd, bool windowed)
    : _windowData{width, height, nativeWnd, windowed}
{
    p_device = std::make_unique<GraphicsDevice>();
    p_cmdQueue = std::make_unique<CommandQueue>(p_device);
    p_fence = std::make_unique<Fence>(p_device);
    p_swapChain = std::make_unique<SwapChain>(p_device, p_cmdQueue, _windowData);
    p_RTV = std::make_unique<DescriptorHeap>(RenderTargetView, p_device, p_swapChain, 3);

    vp = std::make_unique<D3D12_VIEWPORT>(
        0,
        0,
        static_cast<FLOAT>(_windowData.width),
        static_cast<FLOAT>(_windowData.height),
        0.0f,
        1.0f
    );

    rect = std::make_unique<CD3DX12_RECT>(0, 0, _windowData.width, _windowData.height);
}

Developing::Graphics::GraphicsContext::~GraphicsContext() {
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

    p_cmdQueue->_cmdList->RSSetViewports(1u, vp.get());
    p_cmdQueue->_cmdList->RSSetScissorRects(1u, rect.get());

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
    D3D12_CPU_DESCRIPTOR_HANDLE const backBufferView {p_RTV->GetHandle(p_swapChain->GetCurrentBufferIndex())};
    p_cmdQueue->_cmdList->ClearRenderTargetView(backBufferView, DirectX::Colors::PapayaWhip, 0, nullptr);
    p_cmdQueue->_cmdList->OMSetRenderTargets(1u, &backBufferView, FALSE, nullptr);
}
