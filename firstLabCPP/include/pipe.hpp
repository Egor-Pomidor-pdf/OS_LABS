#pragma once
#include "os.h"
#include <cstddef>  // Для size_t

class Pipe {
private:
    PipeHandle fd[2];

public:
    Pipe();
    ~Pipe();
    PipeHandle getReadFd() const { return fd[0]; }
    PipeHandle getWriteFd() const { return fd[1]; }
    ssize_t read(char* buf, size_t size);
    ssize_t write(const char* buf, size_t size);
};