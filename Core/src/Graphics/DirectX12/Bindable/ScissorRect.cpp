#include "pch.h"
#include "ScissorRect.h"

#include "Graphics/GraphicsContext.h"


Developing::Graphics::ScissorRect::ScissorRect(long left, long top, long right, long bottom)
    : Bindable{}
{
    _rect = CD3DX12_RECT{left, top, right, bottom};
}

Developing::Graphics::ScissorRect::~ScissorRect() {
}

void Developing::Graphics::ScissorRect::Bind(GraphicsContext& gfx) noexcept {
    gfx.GetCmdList().RSSetScissorRects(1u, &_rect);
}

std::string Developing::Graphics::ScissorRect::GetUID() const noexcept {
    return "";
}
