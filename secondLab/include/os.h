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
