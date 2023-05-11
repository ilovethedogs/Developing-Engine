#pragma once

namespace Developing::Graphics {
    class GraphicsContext;

    class CommandAllocator {
    public:
        CommandAllocator(GraphicsContext& gfx, D3D12_COMMAND_LIST_TYPE type);
        ~CommandAllocator() = default;

        [[nodiscard]] D3D12_COMMAND_LIST_TYPE GetType() const;
        [[nodiscard]] ID3D12CommandAllocator* GetAllocator();

        void Reset();
    private:
        D3D12_COMMAND_LIST_TYPE _type;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> p_cmdAllocator;
    };
}

