#pragma once


#ifdef _WIN32
#include <windows.h>
using ThreadHandle = HANDLE;
#else
#include <pthread.h>
using ThreadHandle = pthread_t;
#endif

 

int ThreadCreate(ThreadHandle* handle, void* (*func)(void*), void* arg);
void ThreadJoin(ThreadHandle handle);
bool trySpawnThread();
void threadFinished();
void* sortPart(void* arg);



// int CreatePipe(PipeHandle fd[2]);
// int PipeRead(PipeHandle fd, char* buf, size_t size);
// int PipeWrite(PipeHandle fd, const char* buf, size_t size);
// int ClosePipe(PipeHandle fd);
// ProcessHandle CreateChildProcess(const char* exe, char* const* argv, PipeHandle stdin_handle);
// int WaitProcess(ProcessHandle pid);
// int Dup2(PipeHandle oldfd, int newfd);
// ProcessHandle Fork(); 
// int Exec(const char* exe, char* const* argv); 