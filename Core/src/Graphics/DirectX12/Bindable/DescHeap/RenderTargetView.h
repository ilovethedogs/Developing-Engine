#pragma once

#include "Graphics/DirectX12/Bindable/DescHeap/DescriptorHeap.h"

namespace Developing::Graphics {
    class GraphicsDevice;
    class SwapChain;

    class RenderTargetView : public DescriptorHeap {
    public:
        RenderTargetView(std::unique_ptr<GraphicsDevice> const& p_device, std::unique_ptr<SwapChain> const& p_swapChain, uint16_t num);
        virtual ~RenderTargetView() override;

        void Clear(GraphicsContext& gfx) noexcept;
        void Bind(GraphicsContext& gfx) noexcept override;
        [[nodiscard]] std::string GetUID() const noexcept override;
    };
}

