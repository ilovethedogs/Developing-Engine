#include "pch.h"
#include "Buffer.h"

Developing::Graphics::Buffer::Buffer(GraphicsContext& gfx, Type type, UINT size, UINT stride)
    : _size{size}, _stride{stride}
{
    D3D12_HEAP_PROPERTIES heap_prop {};
    D3D12_RESOURCE_DESC desc {CD3DX12_RESOURCE_DESC::Buffer{size}};
    D3D12_RESOURCE_STATES state;

    switch (type) {
        case Type::VertexBuffer:
            heap_prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            state = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
            break;
        case Type::IndexBuffer:
            heap_prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            state = D3D12_RESOURCE_STATE_INDEX_BUFFER;
            break;
        default:
            break;
    }

    Init(gfx, heap_prop, desc, state);
}

void Developing::Graphics::Buffer::Bind(GraphicsContext& gfx) noexcept {
}

std::string Developing::Graphics::Buffer::GetUID() const noexcept {
    return Resource::GetUID();
}
