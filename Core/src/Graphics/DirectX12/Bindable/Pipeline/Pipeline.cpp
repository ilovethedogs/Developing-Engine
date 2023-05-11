#include "pch.h"
#include "Pipeline.h"

#include "Graphics/GraphicsContext.h"

Developing::Graphics::Pipeline::Pipeline(GraphicsContext& gfx, std::string&& tag)
    : _tag{std::forward<std::string>(tag)}
{
}

Developing::Graphics::Pipeline::Pipeline(GraphicsContext& gfx, char const* tag)
    : Pipeline{gfx, std::string{tag}}
{
}

Developing::Graphics::Pipeline::Pipeline(GraphicsContext& gfx)
    : Pipeline{gfx, std::string{"Yeah"}}
{
}

void Developing::Graphics::Pipeline::Bind(GraphicsContext& gfx) noexcept {
}

std::string Developing::Graphics::Pipeline::GenerateUID() {
}

std::string Developing::Graphics::Pipeline::GetUID() const noexcept {
}

D3D12_GRAPHICS_PIPELINE_STATE_DESC& Developing::Graphics::Pipeline::GetPipelineDesc() {
    return _desc;
}
