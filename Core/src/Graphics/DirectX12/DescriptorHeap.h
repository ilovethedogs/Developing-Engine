#pragma once

#define GET_FN(x) (Lookup<x>::create)
#define CREATE(device, type, ...) ((device)->*(GET_FN(type)))(__VA_ARGS__)

#define DESC_HEAP_TYPES    \
    F(RenderTargetView)    \
    F(DepthStencilView)    \
    F(ConstantBufferView)  \
    F(ShaderResourceView)  \
    F(UnorderedAccessView)

namespace Developing::Graphics {
        enum DescHeapType {
            #define F(x) x##,
                DESC_HEAP_TYPES
            #undef F
                ELEMENT_TYPE_SIZE
        }; 

        // static lookup table
        template <DescHeapType> struct Lookup {
            static constexpr bool valid {false};
        };
        template <> struct Lookup<DescHeapType::RenderTargetView> {
            static constexpr D3D12_DESCRIPTOR_HEAP_TYPE sys_type {D3D12_DESCRIPTOR_HEAP_TYPE_RTV};
            static constexpr void (ID3D12Device::*create)(ID3D12Resource*, D3D12_RENDER_TARGET_VIEW_DESC const*, D3D12_CPU_DESCRIPTOR_HANDLE) {&ID3D12Device::CreateRenderTargetView};
            static constexpr char const* code {"RTV"};
            static constexpr bool valid {true};
        };
        template <> struct Lookup<DescHeapType::DepthStencilView> {
            static constexpr D3D12_DESCRIPTOR_HEAP_TYPE sys_type {D3D12_DESCRIPTOR_HEAP_TYPE_DSV};
            static constexpr void (ID3D12Device::*create)(ID3D12Resource*, D3D12_DEPTH_STENCIL_VIEW_DESC const*, D3D12_CPU_DESCRIPTOR_HANDLE) {&ID3D12Device::CreateDepthStencilView};
            static constexpr char const* code {"DSV"};
            static constexpr bool valid {true};
        };
        template <> struct Lookup<DescHeapType::ConstantBufferView> {
            static constexpr D3D12_DESCRIPTOR_HEAP_TYPE sys_type {D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV};
            static constexpr void (ID3D12Device::*create)(D3D12_CONSTANT_BUFFER_VIEW_DESC const*, D3D12_CPU_DESCRIPTOR_HANDLE) {&ID3D12Device::CreateConstantBufferView};
            static constexpr char const* code {"CBV"};
            static constexpr bool valid {true};
        };
        template <> struct Lookup<DescHeapType::ShaderResourceView> {
            static constexpr D3D12_DESCRIPTOR_HEAP_TYPE sys_type {D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV};
            static constexpr void (ID3D12Device::*create)(ID3D12Resource*, D3D12_SHADER_RESOURCE_VIEW_DESC const*, D3D12_CPU_DESCRIPTOR_HANDLE) {&ID3D12Device::CreateShaderResourceView};
            static constexpr char const* code {"SRV"};
            static constexpr bool valid {true};
        };
        template <> struct Lookup<DescHeapType::UnorderedAccessView> {
            static constexpr D3D12_DESCRIPTOR_HEAP_TYPE sys_type {D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV};
            static constexpr void (ID3D12Device::*create)(ID3D12Resource*, ID3D12Resource*, D3D12_UNORDERED_ACCESS_VIEW_DESC const*, D3D12_CPU_DESCRIPTOR_HANDLE) {&ID3D12Device::CreateUnorderedAccessView};
            static constexpr char const* code {"UAV"};
            static constexpr bool valid {true};
        };

        #define F(x) static_assert(Lookup<x>::valid, "Lookup Table Implementation is missing: " #x);
                DESC_HEAP_TYPES
        #undef F

    [[nodiscard]] static constexpr D3D12_DESCRIPTOR_HEAP_TYPE GetType(DescHeapType type) {
        switch (type) {
        #define F(x) case x: return Lookup<x>::sys_type;
            DESC_HEAP_TYPES
        #undef F
        default:
            CORE_ASSERT(false, "Invalid DescHeap Type!");
            return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        } 
    }

    [[nodiscard]] static constexpr char const* GetCode(DescHeapType type) {
        switch (type) {
        #define F(x) case x: return Lookup<x>::code;
            DESC_HEAP_TYPES
        #undef F
        default:
            CORE_ASSERT(false, "Invalid DescHeap Type!");
            return "";
        } 
    }

    class GraphicsDevice;
    class SwapChain;

    class DescriptorHeap {
    public:
        DescriptorHeap(DescHeapType Type, std::unique_ptr<GraphicsDevice> const& p_device, std::unique_ptr<SwapChain> const& p_swapChain, uint16_t num);
        ~DescriptorHeap() = default;

        D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(int16_t idx) const;
    public:
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _descHeap;
        std::vector<D3D12_CPU_DESCRIPTOR_HANDLE>     _handle;
        uint32_t                                     _heapSize;
        uint16_t                                     _num;
    };
}

