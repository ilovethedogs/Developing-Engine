#pragma once

namespace Developing::Graphics {
    class GraphicsContext;

    class RootSignature {
    public:
        RootSignature(GraphicsContext& gfx);

        [[nodiscard]] ID3D12RootSignature* GetSignature();
    private:
        Microsoft::WRL::ComPtr<ID3D12RootSignature> _signature;
    };
}

