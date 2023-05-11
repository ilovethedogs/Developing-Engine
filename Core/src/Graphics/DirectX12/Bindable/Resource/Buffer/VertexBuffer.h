#pragma once

#include "Buffer.h"

namespace Developing::Graphics::Vertex {
    class Buffer;
}

namespace Developing::Graphics {
    class VertexBuffer : public Buffer {
    public:
        VertexBuffer(GraphicsContext& gfx, std::string&& tag, Vertex::Buffer const& buf);
        VertexBuffer(GraphicsContext& gfx, char const* tag, Vertex::Buffer const& buf);
        VertexBuffer(GraphicsContext& gfx, Vertex::Buffer&& buf);
        virtual ~VertexBuffer() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;

        [[nodiscard]] static std::shared_ptr<VertexBuffer> Resolve(GraphicsContext& gfx, char const* tag, Vertex::Buffer const& buf);
        template <typename... Ignore>
        [[nodiscard]] static std::string GenerateUID(std::string const& tag, Ignore&&... ignore);
        [[nodiscard]] std::string GetUID() const noexcept override;
    private:
        std::string _tag;
        D3D12_VERTEX_BUFFER_VIEW  _vbufView {};
        uint32_t                  _count {};
    };
}
