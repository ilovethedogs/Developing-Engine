#pragma once

#include "Graphics/DirectX12/Bindable/Resource/Resource.h"

namespace Developing::Graphics {
    class RenderTarget : public Resource {
    public:
        RenderTarget();
        virtual ~RenderTarget() override = default;
    };
}

