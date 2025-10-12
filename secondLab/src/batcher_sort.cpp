#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/os.h"
#include "../include/glob.h"
#include "../include/batcher_sort.h"



OddEvenSorter::OddEvenSorter(std::vector<int>& arr, int maxThreads)
    : arr_(arr), maxThreads_(maxThreads), activeThreads_(0) {}


void OddEvenSorter::start() {
   oddEvenMergeSort(0, arr_.size());
}
    
// Функция для обмена элементов, если они стоят в неправильном порядке
void OddEvenSorter::compareAndSwap(int i, int j) {
    if (arr_[i] > arr_[j])
        std::swap(arr_[i], arr_[j]);
}

// Рекурсивная функция слияния (odd-even merge)
void OddEvenSorter::oddEvenMerge(int lo, int n, int r) {
    int m = r * 2;
    if (m < n) {
        oddEvenMerge(lo, n, m);
        oddEvenMerge(lo + r, n, m);
        for (int i = lo + r; i + r < lo + n; i += m)
            compareAndSwap(i, i + r);
    } else {
        compareAndSwap(lo, lo + r);
    }
}

// Основная рекурсивная сортировка Бэтчера
void OddEvenSorter::oddEvenMergeSort(int lo, int n) {

    ThreadHandle handle;

    if (n > 1) {
        int m = n / 2;
        if (trySpawnThread()) {
            ThreadData * data = new ThreadData{this, lo, n};
            ThreadCreate(&handle, sortPart, data);
            ThreadJoin(handle);
        } else {
            oddEvenMergeSort(lo, m);
            oddEvenMergeSort(lo + m, m);
        }
        oddEvenMerge(lo, n, 1);
    }
}



void* OddEvenSorter::sortPart(void* arg) {
    ThreadData* data = (ThreadData*)arg; 
    std::cout << "Thread started. Active threads: " << activeThreads << "\n";
    data->sorter->oddEvenMergeSort(data->lo, data->n); 
    std::cout << "Thread finished. Active threads: " << activeThreads << "\n";
    threadFinished(); 
    delete data;

    return nullptr;
}