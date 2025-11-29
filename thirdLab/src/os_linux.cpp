#include "../include/os.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstring>
#include <string>

FileHandle OpenFile(const std::string &filename)
{
    int fd = open(filename.c_str(), O_RDWR | O_CREAT, 0666);
    if (fd == -1)
        perror("open");
    return fd;
}

void SetFileSize(FileHandle file, size_t size)
{
    if (ftruncate(file, size) == -1)
    {
        perror("ftruncate");
    }
}

void *MapFile(FileHandle file, size_t size)
{
    void *addr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return nullptr;
    }
    return addr;
}

void UnmapFile(void *mapped_memory, size_t size)
{
    if (munmap(mapped_memory, size) == -1)
    {
        perror("munmap");
    }
}

void CloseFile(FileHandle file)
{
    if (close(file) == -1)
    {
        perror("close");
    }
}
ProcessHandle CreateChildProcess(const char *exe, char *const *argv)
{
    pid_t pid = Fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
    }
    if (pid == 0)
    {
        Exec(exe, argv);
    }
    return pid;
};

int WaitProcess(ProcessHandle pid)
{
    int status;
    return waitpid(pid, &status, 0);
}

ProcessHandle Fork()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
    }
    return pid;
}

int Exec(const char *exe, char *const *argv)
{
    execvp(exe, argv);
    perror("execvp");
    _exit(1);
    return -1;
}