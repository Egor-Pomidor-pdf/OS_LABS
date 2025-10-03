#include "../include/os.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>  // Для perror

int CreatePipe(PipeHandle fd[2]) {
    return pipe(fd);
}

int PipeRead(PipeHandle fd, char* buf, size_t size) {
    return read(fd, buf, size);
}

int PipeWrite(PipeHandle fd, const char* buf, size_t size) {
    return write(fd, buf, size);
}

int ClosePipe(PipeHandle fd) {
    return close(fd);
}

ProcessHandle CreateChildProcess(const char* exe, char* const* argv, PipeHandle stdin_handle) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        // Child
        if (stdin_handle != INVALID_PIPE_HANDLE) {
            Dup2(stdin_handle, STDIN_FILENO);
            ClosePipe(stdin_handle);
        }
        // Закрыть write end, но поскольку pipe в parent, child не имеет его
        execvp(exe, argv);
        perror("execvp");
        _exit(1);
    }
    return pid;
}

int WaitProcess(ProcessHandle pid) {
    int status;
    return waitpid(pid, &status, 0);
}

int Dup2(PipeHandle oldfd, int newfd) {
    return dup2(oldfd, newfd);
}