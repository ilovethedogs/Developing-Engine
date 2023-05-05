#pragma once

#define VERTEX_ELEMENT_TYPE \
    F(Position2D) \
    F(Position3D) \
    F(Texture2D)  \
    F(Texture3D)  \
    F(Normal)     \
    F(Tangent)    \
    F(Binormal)   \
    F(Color3)     \
    F(Color4) 

namespace Developing::Graphics::Vertex {
    class Element {
    public:
        enum Type {
        #define F(x) x##,
            VERTEX_ELEMENT_TYPE
        #undef F
            ELEMENT_TYPE_SIZE
        };        

        // static Look-up Table
        template <Type> struct Lookup {
            static constexpr bool valid {false};
        };
        template<> struct Lookup<Position2D> {
            using sys_type = DirectX::XMFLOAT2;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32_FLOAT};
            static constexpr char const* hlsl_semantic {"POSITION"};
            static constexpr char const* code {"P2"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Position3D> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"POSITION"};
            static constexpr char const* code {"P3"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Texture2D> {
            using sys_type = DirectX::XMFLOAT2;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32_FLOAT};
            static constexpr char const* hlsl_semantic {"TEXCOORD"};
            static constexpr char const* code {"T2"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Texture3D> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"TEXCOORD"};
            static constexpr char const* code {"T3"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Normal> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"NORMAL"};
            static constexpr char const* code {"N"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Tangent> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"TANGENT"};
            static constexpr char const* code {"Nt"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Binormal> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"BINORMAL"};
            static constexpr char const* code {"Nb"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Color3> {
            using sys_type = DirectX::XMFLOAT3;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32_FLOAT};
            static constexpr char const* hlsl_semantic {"COLOR"};
            static constexpr char const* code {"c3"};
            static constexpr bool valid {true};
        };
        template<> struct Lookup<Color4> {
            using sys_type = DirectX::XMFLOAT4;
            static constexpr DXGI_FORMAT dxgi_format {DXGI_FORMAT_R32G32B32A32_FLOAT};
            static constexpr char const* hlsl_semantic {"COLOR"};
            static constexpr char const* code {"c4"};
            static constexpr bool valid {true};
        };

        #define F(x) static_assert(Lookup<x>::valid, "Lookup table implentation is missing: " #x);
            VERTEX_ELEMENT_TYPE
        #undef F
    public:
        Element(Type type, UINT semantic_index, UINT offset);

        [[nodiscard]] static constexpr UINT Size(Type type);
        [[nodiscard]] static constexpr std::string GetCode(Type type);
        [[nodiscard]] struct D3D12_INPUT_ELEMENT_DESC GetDesc() const;

        [[nodiscard]] size_t GetOffset() const;
        [[nodiscard]] Type GetType() const;
    private:
        template <Element::Type type>
        [[nodiscard]] static constexpr D3D12_INPUT_ELEMENT_DESC GenerateDesc(UINT const _semantic_index, UINT const _offset) {
            return {
                Element::Lookup<type>::hlsl_semantic,
                _semantic_index,
                Element::Lookup<type>::dxgi_format,
                0,
                _offset,
                D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
                0};
        }
    private:
        Type type;
        UINT semanticIndex;
        UINT offset;
    };

    class Layout {
    public:
        Layout() = default;

        Layout& Append(Element::Type type);

        template <Element::Type T>
        [[nodiscard]] Element const& Resolve(size_t i = 0u) const {
            for (auto const& e : elements) {
                auto cnt {0u};
                if (e.GetType() == T) {
                    if (cnt == i)
                        return e;
                    ++cnt;
                }
            } 
            CORE_ASSERT(false, "Element Resolving Failed!");
            return elements.front();
        }

        [[nodiscard]] Element const& At(size_t const i) const;

        [[nodiscard]] std::vector<D3D12_INPUT_ELEMENT_DESC> GenerateLayout() const;
        [[nodiscard]] size_t GetNumOfElem() const;
        [[nodiscard]] size_t SizeBytes() const;
        [[nodiscard]] std::string GetCode() const;
    private:
        std::string code {};
        std::vector<Element> elements;
        std::array<UINT, Element::ELEMENT_TYPE_SIZE> semanticIndex;
        UINT offset;
        size_t bytes;
    };

    class Vertex {
    public:
        Vertex(char* _addr, Layout const* layout);

        template <Element::Type T>
        [[nodiscard]] auto& GetAttr(size_t i = 0u) {
            auto pAttr {addr + layout->Resolve<T>(i).GetOffset()};
            return *reinterpret_cast<typename Element::Lookup<T>::sys_type*>(pAttr);
        }

        template <typename First, typename ...Last>
        void SetAttributes(size_t idx, First&& first, Last&&... last) {
            SetAttributes(idx, first);
            SetAttributes(idx + 1, std::forward<Last>(last));
        }

        template <typename T>
        void SetAttributes(size_t idx, T&& value) {
            auto const& elem {layout->At(idx)};
            auto const loc {addr + elem.GetOffset()};
            switch (elem.GetType()) {
            #define F(x) case Element::##x: SetAttribute<Element::##x>(loc, std::forward<T>(value)); break;
                VERTEX_ELEMENT_TYPE
            #undef F
            default:
                CORE_ASSERT(false, "Invalid Buffer Elem Type!");
                break;
            }
        }
    private:
        template <Element::Type DstType, typename SrcType>
        void SetAttribute(char* loc,  SrcType&& value) {
            using Dst = typename Element::Lookup<DstType>::sys_type;
            if constexpr (std::is_assignable_v<Dst, SrcType>) 
                *reinterpret_cast<Dst*>(loc) = value;
            else
                CORE_ASSERT(false, "Parameter attribute type mismatch");
        }
    private:
        char* addr;
        Layout const* layout;
    };

    class Buffer {
    public:
        Buffer(Layout layout, size_t capacity);
        ~Buffer() = default;

        void Destroy();

        [[nodiscard]] size_t GetSizeBytes() const;
        [[nodiscard]] char const* GetData() const;
        [[nodiscard]] Layout const& GetLayout() const;
        [[nodiscard]] size_t GetNumOfVertices() const;

        [[nodiscard]] Vertex operator[](size_t i) noexcept {
		    CORE_ASSERT(i < num_of_vertices, "invalid index!");
			return Vertex{&buf[layout.GetNumOfElem() * i], &layout};
        }

        template <typename ...Params>
        void Append(Params&&... params) noexcept {
            CORE_ASSERT(sizeof...(params) == layout.GetNumOfElem(), "Params count doesn't match number of vertex elements!"); 
            CORE_ASSERT(num_of_vertices < capacity, "Buffer Overflow!"); 
            ++num_of_vertices;
            Vertex{top, &layout}.SetAttributes(0u, std::forward<Params>(params)...);
            top += layout.SizeBytes();
        }
    private:
        /**
         * Stack
         */
        char* buf {};
        char* top {nullptr};
        size_t size_bytes;
        Layout layout {};
        size_t capacity;
        size_t num_of_vertices;
    };
}

#ifndef VERTEX_IMPL_SOURCE
#undef VERTEX_ELEMENT_TYPE
#endif
