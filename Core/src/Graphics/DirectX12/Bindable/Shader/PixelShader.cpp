#include "pch.h"
#include "PixelShader.h"
#include "Graphics/DirectX12/Bindable/BindableResolver.h"

#include <d3dcompiler.h>

#include "Util/StringConverter.h"

Developing::Graphics::PixelShader::PixelShader(GraphicsContext& gfx, std::string&& path) {
    D3DReadFileToBlob(Util::StringConverter::to_wstring(path).data(), p_blob.ReleaseAndGetAddressOf());
    _byteCode = {p_blob->GetBufferPointer(), p_blob->GetBufferSize()};
}

Developing::Graphics::PixelShader::PixelShader(GraphicsContext& gfx, char const* path)
    : PixelShader{gfx, path}
{
}

void Developing::Graphics::PixelShader::Bind(GraphicsContext& gfx) noexcept {
}

std::shared_ptr<Developing::Graphics::PixelShader> Developing::Graphics::PixelShader::Resolve(std::string const& path) {
    return BindableResolver::Resolve<PixelShader>(path);
}

std::string Developing::Graphics::PixelShader::GenerateUID(std::string const& path) {
    using namespace std::string_literals;
    return typeid(PixelShader).name() + "#"s + path;
}

std::string Developing::Graphics::PixelShader::GetUID() const noexcept {
    return GenerateUID(path);
}
