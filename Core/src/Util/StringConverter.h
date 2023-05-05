#pragma once

namespace Developing::Util {
    class StringConverter {
    public:
        static std::wstring to_wstring(std::string const& str) noexcept;
        static std::string  to_nstring(std::wstring const& str) noexcept;
    };
}

