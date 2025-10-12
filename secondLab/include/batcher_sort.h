#pragma once
#include <vector>
#include "mutex.h"
#include "os.h"

class OddEvenSorter {
public:
    OddEvenSorter(std::vector<int>& arr, int maxThreads);
    void start();

private:
    void oddEvenMergeSort(int lo, int n);                  
    void oddEvenMerge(int lo, int n, int r);  
    void compareAndSwap(int i, int j);        
    static void* sortPart(void* arg);         

    struct ThreadData {
        OddEvenSorter* sorter;
        int lo;                
        int n;                
    };

    std::vector<int>& arr_;
    int maxThreads_;
    int activeThreads_;
    Mutex globalLock_;
};