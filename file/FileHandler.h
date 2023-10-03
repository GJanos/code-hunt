#pragma once

#include <fstream>


class FileHandler {
public:
    std::string file_name;

    explicit FileHandler(std::string file_name);

    void write(const std::string &data);

    std::string read();

    void compile_user_code();

    ~FileHandler();

private:
    std::ofstream _file;
};

