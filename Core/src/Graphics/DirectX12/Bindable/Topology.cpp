#include "pch.h"
#include "Topology.h"

#include "Graphics/DirectX12/Bindable/BindableResolver.h"

Developing::Graphics::Topology::Topology(GraphicsContext& gfx, D3D12_PRIMITIVE_TOPOLOGY type)
    : _type{type}
{
}

void Developing::Graphics::Topology::Bind(GraphicsContext& gfx) noexcept {
}

std::shared_ptr<Developing::Graphics::Topology> Developing::Graphics::Topology::Resolve(GraphicsContext& gfx, D3D12_PRIMITIVE_TOPOLOGY type) {
    return BindableResolver::Resolve<Topology>(gfx, type);
}

std::string Developing::Graphics::Topology::GenerateUID(D3D12_PRIMITIVE_TOPOLOGY type) {
    using namespace std::string_literals;
    return typeid(Topology).name() + "#"s + std::to_string(type);
}

std::string Developing::Graphics::Topology::GetUID() const noexcept {
    return GenerateUID(_type);
}
