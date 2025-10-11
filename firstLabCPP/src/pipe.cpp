#include "../include/pipe.hpp"
#include <stdexcept>  

Pipe::Pipe() {
    if (CreatePipe(fd) != 0) {
        throw std::runtime_error("Failed to create pipe");
    }
}

Pipe::~Pipe() {
    ClosePipe(fd[0]);
    ClosePipe(fd[1]);
}

ssize_t Pipe::read(char* buf, size_t size) {
    return PipeRead(fd[0], buf, size);
}

ssize_t Pipe::write(const char* buf, size_t size) {
    return PipeWrite(fd[1], buf, size);
}