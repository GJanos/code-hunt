#include "Exception.h"

FileException::FileException(const std::string& msg) : message("File Error: " + msg) {}

const char* FileException::what() const noexcept {
    return message.c_str();
}

CompilationException::CompilationException(const std::string& msg) : message("Compilation Error: " + msg) {}

const char* CompilationException::what() const noexcept {
    return message.c_str();
}