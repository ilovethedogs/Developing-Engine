#include "pch.h"
#include "VertexBuffer.h"

#include "Graphics/GraphicsContext.h"
#include "Graphics/DirectX12/Vertex.h"
#include "Graphics/DirectX12/Bindable/BindableResolver.h"

Developing::Graphics::VertexBuffer::VertexBuffer(GraphicsContext& gfx, std::string&& tag, Vertex::Buffer const& buf)
    : Buffer{gfx, Buffer::Type::VertexBuffer, static_cast<UINT>(buf.GetSizeBytes()), static_cast<UINT>(buf.GetLayout().GetStride())},
      _tag{std::move(tag)}
{
    void* data {nullptr};
    CD3DX12_RANGE range {0, 0};
    _resource->Map(0u, &range, &data);
    ::memcpy(data, buf.GetData(), _size);
    _resource->Unmap(0u, nullptr);

    _vbufView.BufferLocation = _resource->GetGPUVirtualAddress();
    _vbufView.StrideInBytes = _stride;
    _vbufView.SizeInBytes = _size;
}

Developing::Graphics::VertexBuffer::VertexBuffer(GraphicsContext& gfx, char const* tag, Vertex::Buffer const& buf)
    : VertexBuffer{gfx, std::string{tag}, buf}
{
}

Developing::Graphics::VertexBuffer::VertexBuffer(GraphicsContext& gfx, Vertex::Buffer&& buf)
    : VertexBuffer{gfx, std::string{"yeah"}, std::move(buf)}
{
}

void Developing::Graphics::VertexBuffer::Bind(GraphicsContext& gfx) noexcept {
    gfx.GetCmdList().IASetVertexBuffers(0u, 1u, &_vbufView);
}

std::shared_ptr<Developing::Graphics::VertexBuffer> Developing::Graphics::VertexBuffer::Resolve(GraphicsContext& gfx, char const* tag, Vertex::Buffer const& buf) {
    return BindableResolver<VertexBuffer>(gfx, tag, buf);
}

template <typename ... Ignore>
std::string Developing::Graphics::VertexBuffer::GenerateUID(std::string const& tag, Ignore&&... ignore) {
    using namespace std::string_literals;
    return typeid(VertexBuffer).name() + "#"s + tag;
}

std::string Developing::Graphics::VertexBuffer::GetUID() const noexcept {
    return Bindable::GetUID();
}
