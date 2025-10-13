#include "../include/os.h"
#include <windows.h>
#include <iostream>

int ThreadCreate(ThreadHandle* handle, void* (*func)(void*), void* arg) {
    *handle = CreateThread(
        nullptr,           // security attributes
        0,                 // stack size (0 = default)
        (LPTHREAD_START_ROUTINE)func, // функция потока
        arg,               // аргумент
        0,                 // creation flags
        nullptr            // thread id (не нужен)
    );

    if (*handle == nullptr) {
        std::cerr << "CreateThread failed, error: " << GetLastError() << "\n";
        return -1;
    }
    return 0;
}

void ThreadJoin(ThreadHandle handle) {
    DWORD res = WaitForSingleObject(handle, INFINITE);
    if (res != WAIT_OBJECT_0) {
        std::cerr << "WaitForSingleObject failed, error: " << GetLastError() << "\n";
    }
    CloseHandle(handle);  // закрываем дескриптор потока
}

// bool trySpawnThread() {
//     bool result = false;
//     globalLock.lock();           
//     if (activeThreads < maxThreads) {
//         activeThreads++;       
//         result = true;
//     }
//     globalLock.unlock();     
//     return result;
// }

// void threadFinished() {
//     globalLock.lock();
//     activeThreads--;               
//     globalLock.unlock();
// }
