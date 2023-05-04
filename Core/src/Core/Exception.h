#pragma once

namespace Developing::Core {
    class Exception : public std::exception {
    public:
        Exception(int line, char const* file) noexcept;
        [[nodiscard]] char const* what() const noexcept override;
        [[nodiscard]] virtual char const* GetType() const noexcept;
        [[nodiscard]] int GetLine() const noexcept;
        [[nodiscard]] std::string const& GetFile() const noexcept;
        [[nodiscard]] std::string GetOriginString() const noexcept;
    private:
        int line;
        std::string file;
    protected:
        mutable std::string whatBuffer;
    };
}

