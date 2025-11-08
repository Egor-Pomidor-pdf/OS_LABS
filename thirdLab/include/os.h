#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
typedef HANDLE FileHandle;
typedef HANDLE ProcessHandle;
typedef HANDLE PipeHandle;
#define INVALID_PIPE_HANDLE INVALID_HANDLE_VALUE
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef int FileHandle;
typedef int PipeHandle;
typedef pid_t ProcessHandle;
#define INVALID_PIPE_HANDLE -1
#endif

FileHandle OpenFile(const std::string &filename);
void SetFileSize(FileHandle file, size_t size);
void *MapFile(FileHandle file, size_t size);
void UnmapFile(void *mapped_memory, size_t size);

void CloseFile(FileHandle file);
ProcessHandle CreateChildProcess(const char *exe, char *const *argv);
int WaitProcess(ProcessHandle pid);
ProcessHandle Fork();
int Exec(const char *exe, char *const *argv);