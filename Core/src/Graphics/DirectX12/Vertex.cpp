#include "pch.h"
#define VERTEX_IMPL_SOURCE
#include "Vertex.h"

namespace Developing::Graphics::Vertex {
    Element::Element(Type type, UINT semantic_index, UINT offset)
        : type{type}, semanticIndex{semantic_index}, offset(offset)
    {
    }

    D3D12_INPUT_ELEMENT_DESC Element::GetDesc() const {
        switch (type) {
        #define F(x) case x: return GenerateDesc<x>(semanticIndex, offset);
            VERTEX_ELEMENT_TYPE
        #undef F
        default:
            CORE_ASSERT(false, "Invalid Buffer Element Type");
            return D3D12_INPUT_ELEMENT_DESC{};
        }
    }

    size_t Element::GetOffset() const {
        return offset;
    }

    Element::Type Element::GetType() const {
        return type;
    }

    constexpr UINT Element::Size(Type type) {
        switch (type) {
        #define F(x) case x: return static_cast<UINT>(sizeof(Lookup<x>::sys_type));
            VERTEX_ELEMENT_TYPE
        #undef F
        default:
            CORE_ASSERT(false, "Invalid Buffer Element Type");
            return 0;
        }
    }

    constexpr std::string Element::GetCode(Type type) {
        switch (type) {
        #define F(x) case x: return std::string{Lookup<x>::code};
            VERTEX_ELEMENT_TYPE
        #undef F
        default:
            CORE_ASSERT(false, "Invalid Buffer Element Type");
            return "";
        }
    }

    Layout& Layout::Append(Element::Type type) {
        elements.emplace_back(type, semanticIndex[type], offset);
        offset += Element::Size(type);
        ++semanticIndex[type];
        code += Element::GetCode(type);

        return *this;
    }

    Element const& Layout::At(size_t const i) const {
        return elements[i];
    }

    std::vector<D3D12_INPUT_ELEMENT_DESC> Layout::GenerateLayout() const {
        std::vector<D3D12_INPUT_ELEMENT_DESC> result;
        result.reserve(elements.size());
        std::ranges::transform(elements, std::back_inserter(result), [](auto& e) {
            return e.GetDesc();
        });
        return result;
    }

    size_t Layout::GetNumOfElem() const {
        return elements.size();
    }

    size_t Layout::SizeBytes() const {
        return offset;
    }

    std::string Layout::GetCode() const {
        return code;
    }

    Vertex::Vertex(char* _addr, Layout const* layout)
        : addr{_addr}, layout{layout}
    {
    }

    Buffer::Buffer(Layout layout, size_t capacity)
        : layout{layout}, capacity{capacity}
    {
        size_bytes = sizeof(char) * layout.SizeBytes() * capacity;
        buf = new char[size_bytes];
        top = buf;
    }

    void Buffer::Destroy() {
        delete buf;
        buf = nullptr;
    }

    size_t Buffer::GetSizeBytes() const {
        return size_bytes;
    }

    char const* Buffer::GetData() const {
        return const_cast<char*>(buf);
    }

    Layout const& Buffer::GetLayout() const {
        return layout;
    }

    size_t Buffer::GetNumOfVertices() const {
        return num_of_vertices;
    }
}
