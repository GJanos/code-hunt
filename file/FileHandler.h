#pragma once

#include <fstream>
#include <optional>

namespace gj {
    typedef int (*UserFuncType)(int);

    struct CompilationResult {
        std::optional<std::string> error;
        UserFuncType userFunc;
    };

    class FileHandler {
    public:
        std::string file_name;

        explicit FileHandler(std::string file_name);

        void write(const std::string &data);

        std::string read();

        void compile_user_code();

        UserFuncType fetchUserFunction(void*& handle);

        CompilationResult getUserFunction(const std::string &user_typed_code, void *&handle);

        ~FileHandler();

    private:
        std::ofstream _file;
    };
}


