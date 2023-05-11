#pragma once

namespace Developing::Graphics {
    class GraphicsContext;
    class CommandAllocator;

    class CommandList {
    public:
        CommandList(GraphicsContext& gfx, std::unique_ptr<CommandAllocator> const& allocator);
        ~CommandList() = default;

        void Reset(std::unique_ptr<CommandAllocator> const& allocator);
    private:
        D3D12_COMMAND_LIST_TYPE _type {};
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> p_cmdList;
    };
}

