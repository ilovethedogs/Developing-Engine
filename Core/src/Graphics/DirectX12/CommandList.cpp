#include "pch.h"
#include "CommandList.h"

#include "GraphicsDevice.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/DirectX12/CommandAllocator.h"

Developing::Graphics::CommandList::CommandList(GraphicsContext& gfx, std::unique_ptr<CommandAllocator> const& allocator)
    : _type {allocator->GetType()}
{
    gfx.GetDeviceImpl()->GetDevice()->CreateCommandList(
        0u,
        _type,
        allocator->GetAllocator(),
        nullptr,
        IID_PPV_ARGS(p_cmdList.ReleaseAndGetAddressOf())
    );

    p_cmdList->Close();
}

void Developing::Graphics::CommandList::Reset(std::unique_ptr<CommandAllocator> const& allocator) {
    p_cmdList->Reset(allocator->GetAllocator(), nullptr);
}
