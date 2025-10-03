#pragma once

#ifdef _WIN32
#include <windows.h>
typedef HANDLE PipeHandle;
typedef HANDLE ProcessHandle;
#define INVALID_PIPE_HANDLE INVALID_HANDLE_VALUE
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef int PipeHandle;
typedef pid_t ProcessHandle;
#define INVALID_PIPE_HANDLE -1
#endif

// Функции-обёртки (реализуются в os_*.cpp)
int CreatePipe(PipeHandle fd[2]);
int PipeRead(PipeHandle fd, char* buf, size_t size);
int PipeWrite(PipeHandle fd, const char* buf, size_t size);
int ClosePipe(PipeHandle fd);
ProcessHandle CreateChildProcess(const char* exe, char* const* argv, PipeHandle stdin_handle);
int WaitProcess(ProcessHandle pid);
int Dup2(PipeHandle oldfd, int newfd);  // Может быть no-op на Win