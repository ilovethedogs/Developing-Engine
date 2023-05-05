#pragma once

#include "Bindable.h"

namespace Developing::Graphics::Vertex {
    class Buffer;
}

namespace Developing::Graphics {
    class VertexBuffer : public Bindable {
    public:
        VertexBuffer(std::string const& tag, Vertex::Buffer const& buf);
        VertexBuffer(Vertex::Buffer const& buf);
        virtual ~VertexBuffer() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;

        [[nodiscard]] static std::shared_ptr<VertexBuffer> Resolve(std::string const& tag, Vertex::VertexBuffer const& vbuf);
        template <typename... Ignore>
        [[nodiscard]] static std::string GenerateUID(std::string const& tag, Ignore&&... ignore);
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        std::string _tag;
        UINT _stride;
        Microsoft::WRL::ComPtr<ID3D12Resource> _vbuf;
        D3D12_VERTEX_BUFFER_VIEW               _vbufView {};
        uint32_t                               _count {} ;
    };
}
