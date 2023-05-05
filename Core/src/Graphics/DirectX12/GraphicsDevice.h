#pragma once

namespace Developing::Graphics {
    class GraphicsDevice {
    public:
        GraphicsDevice();
        ~GraphicsDevice() = default;

        [[nodiscard]] IDXGIFactory* GetDxgi() const { return _dxgi.Get(); }
        [[nodiscard]] ID3D12Device* GetDevice() const { return _device.Get(); }
    public:
        Microsoft::WRL::ComPtr<ID3D12Debug>   _debug;
        Microsoft::WRL::ComPtr<IDXGIFactory>  _dxgi;
        Microsoft::WRL::ComPtr<ID3D12Device>  _device;
    };
}

