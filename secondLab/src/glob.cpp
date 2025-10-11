#include "../include/mutex.h"

Mutex globalLock;
int activeThreads = 0;
int maxThreads = 4;