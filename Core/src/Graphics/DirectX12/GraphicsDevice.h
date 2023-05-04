#pragma once

#include <d3dx12/d3dx12.h>
#include <d3d12.h>
#include <dxgi.h>

namespace Developing::Graphics {
    class GraphicsDevice {
    public:
        GraphicsDevice();
        ~GraphicsDevice() = default;

        [[nodiscard]] IDXGIFactory* GetDxgi() const { return _dxgi.Get(); }
        [[nodiscard]] ID3D12Device* GetDevice() const { return _device.Get(); }
    private:
        Microsoft::WRL::ComPtr<ID3D12Debug>   _debug;
        Microsoft::WRL::ComPtr<IDXGIFactory>  _dxgi;
        Microsoft::WRL::ComPtr<ID3D12Device>  _device;
    };
}

