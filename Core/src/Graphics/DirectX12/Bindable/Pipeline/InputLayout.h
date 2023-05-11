#pragma once

#include "Bindable.h"
#include "Graphics/DirectX12/Vertex.h"

namespace Developing::Graphics {
    class InputLayout : public Bindable {
    public:
        InputLayout(GraphicsContext& gfx, Vertex::Layout const& layout);
        virtual ~InputLayout() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;

        [[nodiscard]] static std::shared_ptr<InputLayout> Resolve(GraphicsContext& gfx, Vertex::Layout const& layout, ID3DBlob* pVertexShaderByteCode);
        [[nodiscard]] static std::string GenerateUID(Vertex::Layout const& layout);
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        Vertex::Layout _layout;
        std::vector<struct D3D12_INPUT_ELEMENT_DESC> _desc;
    };
}

