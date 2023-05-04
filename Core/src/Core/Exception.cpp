#include "pch.h"
#include "Exception.h"

Developing::Core::Exception::Exception(int line, char const* file) noexcept
    : line{line}, file{file}
{
}

char const* Developing::Core::Exception::what() const noexcept {
    std::ostringstream oss;
    oss << GetType() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

char const* Developing::Core::Exception::GetType() const noexcept {
    return "Exception";
}

int Developing::Core::Exception::GetLine() const noexcept {
    return line;
}

std::string const& Developing::Core::Exception::GetFile() const noexcept {
    return file;
}

std::string Developing::Core::Exception::GetOriginString() const noexcept {
    std::ostringstream oss;
    oss << "[File] " << file << std::endl
        << "[Line] " << line;
    return oss.str();
}
