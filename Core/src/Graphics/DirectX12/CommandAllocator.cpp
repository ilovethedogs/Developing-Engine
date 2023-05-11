#include "pch.h"
#include "CommandAllocator.h"

#include "Graphics/GraphicsContext.h"

Developing::Graphics::CommandAllocator::CommandAllocator(GraphicsContext& gfx, D3D12_COMMAND_LIST_TYPE type)
    : _type{type}
{
    gfx.GetDeviceImpl().CreateCommandAllocator(
        type,
        IID_PPV_ARGS(p_cmdAllocator.ReleaseAndGetAddressOf())
    );
}

D3D12_COMMAND_LIST_TYPE Developing::Graphics::CommandAllocator::GetType() const {
    return _type;
}

ID3D12CommandAllocator* Developing::Graphics::CommandAllocator::GetAllocator() {
    return p_cmdAllocator.Get();
}

void Developing::Graphics::CommandAllocator::Reset() {
    p_cmdAllocator->Reset();
}
