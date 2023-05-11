#include "pch.h"
#include "InputLayout.h"

#include "Graphics/DirectX12/Bindable/BindableResolver.h"

Developing::Graphics::InputLayout::InputLayout(GraphicsContext& gfx, Vertex::Layout const& layout)
    : _layout{layout}
{
    auto const desc {layout.GenerateLayout()};
    _desc.reserve(desc.size());
    std::ranges::move(desc, std::back_inserter(_desc));
}

void Developing::Graphics::InputLayout::Bind(GraphicsContext& gfx) noexcept {
}

std::shared_ptr<Developing::Graphics::InputLayout> Developing::Graphics::InputLayout::Resolve(GraphicsContext& gfx, Vertex::Layout const& layout, ID3DBlob* pVertexShaderByteCode) {
    return BindableResolver::Resolve<InputLayout>(gfx, layout);
}

std::string Developing::Graphics::InputLayout::GenerateUID(Vertex::Layout const& layout) {
    using namespace std::string_literals;
    return typeid(InputLayout).name() + "#"s + layout.GetCode();
}

std::string Developing::Graphics::InputLayout::GetUID() const noexcept {
    return GenerateUID(_layout);
}
