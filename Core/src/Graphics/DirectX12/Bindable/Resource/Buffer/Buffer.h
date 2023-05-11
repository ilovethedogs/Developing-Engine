#pragma once

#include "Graphics/DirectX12/Bindable/Resource/Resource.h"

namespace Developing::Graphics {

    class Buffer : public Resource {
    public:
        enum class Type {
            VertexBuffer,
            IndexBuffer,
        };
    public:
        Buffer(GraphicsContext& gfx, Type type, UINT size, UINT stride);
        virtual ~Buffer() override = default;

        void Bind(GraphicsContext& gfx) noexcept override;
        [[nodiscard]] std::string GetUID() const noexcept override;
    protected:
        UINT _size;
        UINT _stride;
    };
}

