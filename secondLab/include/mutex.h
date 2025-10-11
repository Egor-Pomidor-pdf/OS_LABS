#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

class Mutex {
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
#ifdef _WIN32
    CRITICAL_SECTION lock_;
#else
    pthread_mutex_t lock_;
#endif
};
