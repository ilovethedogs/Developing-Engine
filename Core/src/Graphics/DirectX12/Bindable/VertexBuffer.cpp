#include "pch.h"
#include "VertexBuffer.h"

#include "Graphics/DirectX12/Vertex.h"

Developing::Graphics::VertexBuffer::VertexBuffer(std::string const& tag, Vertex::Buffer const& buf)
    : _tag{std::move(tag)}, _stride{static_cast<UINT>(buf.GetLayout().SizeBytes())}
{
    
}

Developing::Graphics::VertexBuffer::VertexBuffer(Vertex::Buffer const& buf) {
}

void Developing::Graphics::VertexBuffer::Bind(GraphicsContext& gfx) noexcept {
}

template <typename ... Ignore>
std::string Developing::Graphics::VertexBuffer::GenerateUID(std::string const& tag, Ignore&&... ignore) {
}

std::string Developing::Graphics::VertexBuffer::GetUID() const noexcept {
    return Bindable::GetUID();
}
