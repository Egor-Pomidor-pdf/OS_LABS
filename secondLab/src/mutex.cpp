#include "../include/mutex.h"
#include <iostream>

#ifdef _WIN32

Mutex::Mutex() {
    InitializeCriticalSection(&lock_);
}

Mutex::~Mutex() {
    DeleteCriticalSection(&lock_);
}

void Mutex::lock() {
    EnterCriticalSection(&lock_);
}

void Mutex::unlock() {
    LeaveCriticalSection(&lock_);
}

#else // POSIX

Mutex::Mutex() {
    if (pthread_mutex_init(&lock_, nullptr) != 0) {
        std::cerr << "Error: pthread_mutex_init failed\n";
    }
}

Mutex::~Mutex() {
    if (pthread_mutex_destroy(&lock_) != 0) {
        std::cerr << "Error: pthread_mutex_destroy failed\n";
    }
}

void Mutex::lock() {
    if (pthread_mutex_lock(&lock_) != 0) {
        std::cerr << "Error: pthread_mutex_lock failed\n";
    }
}

void Mutex::unlock() {
    if (pthread_mutex_unlock(&lock_) != 0) {
        std::cerr << "Error: pthread_mutex_unlock failed\n";
    }
}

#endif
