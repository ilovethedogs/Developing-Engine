#include "pch.h"
#include "SwapChain.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/DirectX12/GraphicsDevice.h"
#include "Graphics/DirectX12/CommandQueue.h"

namespace Developing::Graphics {
    SwapChain::SwapChain(GraphicsContext& gfx) {
        DXGI_SWAP_CHAIN_DESC sd;
        sd.BufferDesc.Width = static_cast<uint16_t>(gfx.GetWindowData().width); 
        sd.BufferDesc.Height = static_cast<uint16_t>(gfx.GetWindowData().height); 
        sd.BufferDesc.RefreshRate.Numerator = 60; 
        sd.BufferDesc.RefreshRate.Denominator = 1; 
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
        sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        sd.SampleDesc.Count = 1; 
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; 
        sd.BufferCount = NUM_BACK_BUFFERS;
        sd.OutputWindow = gfx.GetWindowData().nativeWnd;
        sd.Windowed = gfx.GetWindowData().windowed;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; 
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

        gfx.GetDeviceImpl()->GetDxgi()->CreateSwapChain(gfx.GetCommandQueueImpl()->GetQueue(), &sd, _swapChain.ReleaseAndGetAddressOf());

        for (auto i {0}; i != NUM_BACK_BUFFERS; ++i)
            _swapChain->GetBuffer(i, IID_PPV_ARGS(&_renderTarget[i]));
    }

    void SwapChain::Present() {
        _swapChain->Present(0u, 0u);
    }

    void SwapChain::Swap() {
        _bufferIdx = (_bufferIdx + 1) % NUM_BACK_BUFFERS;
    }
}
