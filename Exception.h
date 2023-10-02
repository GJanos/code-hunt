#pragma once

#include <exception>
#include <string>

class FileException : public std::exception {
private:
    std::string message;
public:
    explicit FileException(const std::string& msg);
    const char* what() const noexcept override;
};

class CompilationException : public std::exception {
private:
    std::string message;
public:
    explicit CompilationException(const std::string& msg);
    const char* what() const noexcept override;
};
