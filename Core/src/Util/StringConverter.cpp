#include "pch.h"
#include "StringConverter.h"

std::wstring Developing::Util::StringConverter::to_wstring(std::string const& str) noexcept {
    std::wstring result {};
    result.resize(str.size() + 1);
    size_t size;
    mbstowcs_s(&size, result.data(), result.size(), str.c_str(), _TRUNCATE);
    if (size > 0) {
        result.resize(size - 1);
        return result;
    }
    return {};
}

std::string Developing::Util::StringConverter::to_nstring(std::wstring const& str) noexcept {
    std::string result {};
    result.resize(str.size() + 1);
    size_t size;
    wcstombs_s(&size, result.data(), result.size(), str.c_str(), _TRUNCATE);
    result.resize(size - 1);
    return result;
}
