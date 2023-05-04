#include "pch.h"
#include "GraphicsContext.h"

#include <Graphics/DirectX12/GraphicsDevice.h>
#include <Graphics/DirectX12/CommandQueue.h>
#include <Graphics/DirectX12/SwapChain.h>
#include <Graphics/DirectX12/DescriptorHeap.h>

Developing::Graphics::GraphicsContext::GraphicsContext(int width, int height, HWND nativeWnd, bool windowed)
    : _windowData{width, height, nativeWnd, windowed}
{
    p_device = std::make_unique<GraphicsDevice>();
    p_cmdQueue = std::make_unique<CommandQueue>(p_device);
    p_swapChain = std::make_unique<SwapChain>(p_device, p_cmdQueue, _windowData);
    p_RTV = std::make_unique<DescriptorHeap>(RenderTargetView, p_device, p_swapChain, 3);
}

Developing::Graphics::GraphicsContext::~GraphicsContext() {
}
