#include "FileHandler.h"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <dlfcn.h>
#include <iostream>

#include "Exception.h"

using namespace gj;

FileHandler::FileHandler(std::string file_name) : file_name(std::move(file_name)), _file(this->file_name) {
    if (!_file.is_open()) {
        throw FileException("File could not be opened");
    }
}

void FileHandler::write(const std::string &data) {
    std::ofstream file(file_name);
    file << data;
    file.close();
}

std::string FileHandler::read() {
    std::ifstream file(file_name);
    std::string data;
    std::string line;
    while (std::getline(file, line)) {
        data += line + "\n";
    }
    file.close();
    return data;
}

FileHandler::~FileHandler() {
    _file.close();
}

void FileHandler::compile_user_code() {
    pid_t pid = fork();
    if (pid == 0) {
        // This block will be executed by the child process
        execlp("g++", "g++", "-shared", "-o", "../libhunt.so", file_name.c_str(), "-fPIC", (char *) NULL);
        _exit(EXIT_FAILURE);  // exec never returns unless there's an error
    } else if (pid < 0) {
        // Fork failed
        // Handle error here
        throw CompilationException("Fork failed");
    } else {
        // This block will be executed by the parent
        int status;
        waitpid(pid, &status, 0);  // Wait for the child process to exit
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // Compilation succeeded
            std::cout << "Compilation succeeded" << std::endl;
        } else {
            throw CompilationException("Compilation failed");
        }
    }
}

UserFuncType FileHandler::fetchUserFunction(void *&handle) {
    handle = dlopen("../libhunt.so", RTLD_LAZY);
    if (!handle) {
        throw LibraryOpenException("Cannot open library: " + std::string(dlerror()));
    }

    dlerror();
    auto hunt = (UserFuncType) dlsym(handle,
                                     "hunt"); // Change this if you want to make the function name dynamic
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        throw UserFuncNotFoundException("Cannot load symbol 'hunt': " + std::string(dlsym_error));
    }
    return hunt;
}

CompilationResult FileHandler::getUserFunction(const std::string &user_typed_code, void *&handle) {
    try {
        write(user_typed_code);
        compile_user_code();
        auto user_func = fetchUserFunction(handle);
        return {std::nullopt, user_func};
    } catch (const std::exception &e) {
        return {e.what(), nullptr};
    }

}