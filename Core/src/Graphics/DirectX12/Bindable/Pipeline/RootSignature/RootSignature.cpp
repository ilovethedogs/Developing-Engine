#include "pch.h"
#include "RootSignature.h"

#include "Graphics/GraphicsContext.h"

Developing::Graphics::RootSignature::RootSignature(GraphicsContext& gfx) {
    D3D12_ROOT_SIGNATURE_DESC desc {CD3DX12_ROOT_SIGNATURE_DESC(D3D12_DEFAULT)};
    desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    Microsoft::WRL::ComPtr<ID3DBlob> blob_signature;
    Microsoft::WRL::ComPtr<ID3DBlob> blob_error;
    ::D3D12SerializeRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1, blob_signature.ReleaseAndGetAddressOf(), blob_error.ReleaseAndGetAddressOf());
    gfx.GetDeviceImpl().CreateRootSignature(
        0u, 
        blob_signature->GetBufferPointer(), 
        blob_signature->GetBufferSize(), 
        IID_PPV_ARGS(_signature.ReleaseAndGetAddressOf())
    );
}

ID3D12RootSignature* Developing::Graphics::RootSignature::GetSignature() {
    return _signature.Get();
}
