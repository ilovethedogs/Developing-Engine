#pragma once

#include "Graphics/DirectX12/Bindable/Bindable.h"

namespace Developing::Graphics {
    class PixelShader : public Bindable {
    public:
        PixelShader(GraphicsContext& gfx, std::string&& path);
        PixelShader(GraphicsContext& gfx, char const* path);

        virtual ~PixelShader() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;

        [[nodiscard]] static std::shared_ptr<PixelShader> Resolve(std::string const& path);
        [[nodiscard]] static std::string GenerateUID(std::string const& path);
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        std::string path;
        Microsoft::WRL::ComPtr<ID3DBlob> p_blob;
        struct D3D12_SHADER_BYTECODE _byteCode;
    };
}

