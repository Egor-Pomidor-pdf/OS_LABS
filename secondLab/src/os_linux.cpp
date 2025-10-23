#include "../include/os.h"
#include <pthread.h>
#include <errno.h>
#include <stdio.h>   

int ThreadCreate(ThreadHandle* handle, void* (*func)(void*), void* arg) {
    int res = pthread_create(handle, nullptr, func, arg);
    if (res != 0) {
        perror("pthread_create failed");
        return -1;
    }
    return 0;
}

void ThreadJoin(ThreadHandle handle) {
    int res = pthread_join(handle, nullptr);
    if (res != 0) {
        perror("pthread_join failed");
    }
}

