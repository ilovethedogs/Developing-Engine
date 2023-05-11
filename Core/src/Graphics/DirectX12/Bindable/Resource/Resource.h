#pragma once

#include "Graphics/DirectX12/Bindable/Bindable.h"

namespace Developing::Graphics {

    class Resource : public Bindable {
    public:
        Resource() = default;
        virtual ~Resource() override = default;

        void Init(GraphicsContext& gfx, D3D12_HEAP_PROPERTIES cosnt& heap_prop, D3D12_RESOURCE_DESC const& desc, D3D12_RESOURCE_STATES const& init_state);

        void Upload() noexcept;

        virtual void Bind(GraphicsContext& gfx) noexcept override {}

        [[nodiscard]] std::string GetUID() const noexcept override {
            CORE_ASSERT(false, "This is Resource Base Class!");
            return {};
        }
    protected:
        void Transition(ID3D12GraphicsCommandList& cmdList, D3D12_RESOURCE_STATES to);
    protected:
        D3D12_RESOURCE_STATES _state {};
        Microsoft::WRL::ComPtr<ID3D12Resource> _resource;
    };
}
