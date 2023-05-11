#pragma once

#include "Graphics/DirectX12/Bindable/Bindable.h"

namespace Developing::Graphics {
    class VertexShader : public Bindable {
    public:
        VertexShader(GraphicsContext& gfx, std::string&& path);
        VertexShader(GraphicsContext& gfx, char const* path);

        virtual ~VertexShader() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;

        [[nodiscard]] static std::shared_ptr<VertexShader> Resolve(GraphicsContext& gfx, char const* path);
        [[nodiscard]] static std::string GenerateUID(std::string const& path);
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        std::string _path;
        Microsoft::WRL::ComPtr<ID3DBlob> p_blob;
        struct D3D12_SHADER_BYTECODE _byteCode;
    };
}

