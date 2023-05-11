#include "pch.h"
#include "Resource.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/DirectX12/GraphicsDevice.h"

void Developing::Graphics::Resource::Init(GraphicsContext& gfx, D3D12_HEAP_PROPERTIES& heap_prop, D3D12_RESOURCE_DESC const& desc, D3D12_RESOURCE_STATES const& init_state) {
    _state = init_state;

    gfx.GetDeviceImpl()->GetDevice()->CreateCommittedResource(
        &heap_prop,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        _state,
        nullptr,
        IID_PPV_ARGS(_resource.ReleaseAndGetAddressOf())
    );
}

void Developing::Graphics::Resource::Upload() noexcept {
}

void Developing::Graphics::Resource::Transition(ID3D12GraphicsCommandList& cmdList, D3D12_RESOURCE_STATES to) {
    D3D12_RESOURCE_BARRIER const barrier {
        CD3DX12_RESOURCE_BARRIER::Transition(
            _resource.Get(),
            _state,
            to
        )
    };

    cmdList.ResourceBarrier(1u, &barrier);
}
