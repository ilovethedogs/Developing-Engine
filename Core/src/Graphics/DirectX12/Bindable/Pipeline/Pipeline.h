#pragma once

#include "Graphics/DirectX12/Bindable/Bindable.h"

namespace Developing::Graphics {
    class Pipeline : public Bindable {
    public:
        Pipeline(GraphicsContext& gfx, std::string&& tag);
        Pipeline(GraphicsContext& gfx, char const* tag);
        Pipeline(GraphicsContext& gfx);

        virtual ~Pipeline() override;

        [[nodiscard]] D3D12_GRAPHICS_PIPELINE_STATE_DESC& GetPipelineDesc();

        void Bind(GraphicsContext& gfx) noexcept override;
        [[nodiscard]] static std::string GenerateUID();
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        std::string _tag;
        Microsoft::WRL::ComPtr<struct ID3D12PipelineState> p_state;
        struct D3D12_GRAPHICS_PIPELINE_STATE_DESC          _desc {};
    };
}

