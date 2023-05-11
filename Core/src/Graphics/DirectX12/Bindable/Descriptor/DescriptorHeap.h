#pragma once

#include "Graphics/DirectX12/Bindable/Bindable.h"

namespace Developing::Graphics {
    class DescriptorHeap : public Bindable {
    public:
        DescriptorHeap(uint16_t num);
        virtual ~DescriptorHeap() override = default;

        D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(int16_t idx) const;

        void Bind(GraphicsContext& gfx) noexcept override = 0;
        [[nodiscard]] std::string GetUID() const noexcept override {
            CORE_ASSERT(false, "This is DescriptorHeap Base Class!");
            return "";
        }
    public:
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _descHeap;
        std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>     _handle;
        uint32_t                                     _heapSize;
        uint16_t                                     _num;
    };
}

