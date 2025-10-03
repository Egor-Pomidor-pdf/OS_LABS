#include "../include/pipe.hpp"

Pipe::Pipe() {
    if (CreatePipe(fd) != 0) {
        // Обработка ошибки, но для простоты пропустим
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