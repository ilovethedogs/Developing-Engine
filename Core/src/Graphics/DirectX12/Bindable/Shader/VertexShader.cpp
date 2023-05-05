#include "pch.h"
#include "VertexShader.h"
#include "Graphics/DirectX12/Bindable/BindableResolver.h"

#include <d3dcompiler.h>

#include "Util/StringConverter.h"

Developing::Graphics::VertexShader::VertexShader(GraphicsContext& gfx, std::string&& path)
    : path{std::forward<std::string>(path)}
{
    D3DReadFileToBlob(Util::StringConverter::to_wstring(path).data(), p_blob.ReleaseAndGetAddressOf());
    _byteCode = {p_blob->GetBufferPointer(), p_blob->GetBufferSize()};
}

Developing::Graphics::VertexShader::VertexShader(GraphicsContext& gfx, char const* path)
    : VertexShader{gfx, std::string{path}}
{
}

void Developing::Graphics::VertexShader::Bind(GraphicsContext& gfx) noexcept {
}

std::shared_ptr<Developing::Graphics::VertexShader> Developing::Graphics::VertexShader::Resolve(std::string const& path) {
    return BindableResolver::Resolve<VertexShader>(path);
}

std::string Developing::Graphics::VertexShader::GenerateUID(std::string const& path) {
    using namespace std::string_literals;
    return typeid(VertexShader).name() + "#"s + path;
}

std::string Developing::Graphics::VertexShader::GetUID() const noexcept {
    return GenerateUID(path);
}
