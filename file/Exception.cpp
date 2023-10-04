#include "Exception.h"

FileException::FileException(const std::string &msg) :
        message("File Error: " + msg) {}

const char *FileException::what() const noexcept {
    return message.c_str();
}

CompilationException::CompilationException(const std::string &msg) :
        message("Compilation Error: " + msg) {}

const char *CompilationException::what() const noexcept {
    return message.c_str();
}

LibraryOpenException::LibraryOpenException(const std::string &msg) :
        message("Library Open Error: " + msg) {}

const char *LibraryOpenException::what() const noexcept {
    return message.c_str();
}

UserFuncNotFoundException::UserFuncNotFoundException(const std::string &msg) :
        message("User Function Not Found Error: " + msg) {}

const char *UserFuncNotFoundException::what() const noexcept {
    return message.c_str();
}

