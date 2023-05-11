#include "pch.h"
#define VERTEX_IMPL_SOURCE
#include "Vertex.h"

namespace Developing::Graphics::Vertex {
    Element::Element(Type type, UINT semantic_index, UINT offset)
        : _type{type}, _index{semantic_index}, _offset(offset)
    {
    }

    D3D12_INPUT_ELEMENT_DESC Element::GetDesc() const {
        switch (_type) {
        #define F(x) case x: return GenerateDesc<x>(_index, _offset);
            VERTEX_ELEMENT_TYPE
        #undef F
        default:
            CORE_ASSERT(false, "Invalid Buffer Element Type");
            return D3D12_INPUT_ELEMENT_DESC{};
        }
    }

    size_t Element::GetOffset() const {
        return _offset;
    }

    Element::Type Element::GetType() const {
        return _type;
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
        _elements.emplace_back(type, _index[type], _offset);
        _offset += Element::Size(type);
        ++_index[type];
        _code += Element::GetCode(type);

        return *this;
    }

    Element const& Layout::At(size_t const i) const {
        return _elements[i];
    }

    std::vector<D3D12_INPUT_ELEMENT_DESC> Layout::GenerateLayout() const {
        std::vector<D3D12_INPUT_ELEMENT_DESC> result;
        result.reserve(_elements.size());
        std::ranges::transform(_elements, std::back_inserter(result), [](auto& e) {
            return e.GetDesc();
        });
        return result;
    }

    size_t Layout::GetNumOfElem() const {
        return _elements.size();
    }

    size_t Layout::GetStride() const {
        return _offset;
    }

    std::string Layout::GetCode() const {
        return _code;
    }

    Vertex::Vertex(char* _addr, Layout const* layout)
        : _addr{_addr}, _layout{layout}
    {
    }

    Buffer::Buffer(Layout layout, size_t capacity)
        : _layout{layout}, _capacity{capacity}
    {
        _sizeBytes = sizeof(char) * layout.GetStride() * capacity;
        _buf = new char[_sizeBytes];
        _top = _buf;
    }

    void Buffer::Destroy() {
        delete _buf;
        _buf = nullptr;
    }

    size_t Buffer::GetSizeBytes() const {
        return _sizeBytes;
    }

    char const* Buffer::GetData() const {
        return const_cast<char*>(_buf);
    }

    Layout const& Buffer::GetLayout() const {
        return _layout;
    }

    size_t Buffer::GetNumOfVertices() const {
        return _numOfVertices;
    }
}
