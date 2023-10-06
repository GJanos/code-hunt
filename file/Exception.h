#pragma once

#include <exception>
#include <string>

class FileException : public std::exception {
private:
    std::string message;
public:
    explicit FileException(const std::string &msg);

    const char *what() const noexcept override;
};

class CompilationException : public std::exception {
private:
    std::string message;
public:
    explicit CompilationException(const std::string &msg);

    const char *what() const noexcept override;
};

class LibraryOpenException : public std::exception {
private:
    std::string message;
public:
    explicit LibraryOpenException(const std::string &msg);

    const char *what() const noexcept override;
};

class UserFuncNotFoundException : public std::exception {
private:
    std::string message;
public:
    explicit UserFuncNotFoundException(const std::string &msg);

    const char *what() const noexcept override;
};

class ReturnStatementMissingException : public std::exception {
private:
    std::string message;
public:
    explicit ReturnStatementMissingException(const std::string &msg);

    const char *what() const noexcept override;
};
