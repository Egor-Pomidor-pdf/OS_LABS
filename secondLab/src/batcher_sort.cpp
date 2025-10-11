#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/os.h"
#include "../include/glob.h"
#include "../include/batcher_sort.h"


struct ThreadData {
    std::vector<int>* arr; 
    int lo;                
    int n;                
};

// Функция для обмена элементов, если они стоят в неправильном порядке
void compareAndSwap(std::vector<int>& arr, int i, int j) {
    if (arr[i] > arr[j]) std::swap(arr[i], arr[j]);
}

// Рекурсивная функция слияния (odd-even merge)
void oddEvenMerge(std::vector<int>& arr, int lo, int n, int r) {
    int m = r * 2;
    if (m < n) {
        oddEvenMerge(arr, lo, n, m);
        oddEvenMerge(arr, lo + r, n, m);
        for (int i = lo + r; i + r < lo + n; i += m) {
            compareAndSwap(arr, i, i + r);
        }
    } else {
        compareAndSwap(arr, lo, lo + r);
    }
}

// Основная рекурсивная сортировка Бэтчера
void oddEvenMergeSort(std::vector<int>& arr, int lo, int n) {

    ThreadHandle handle;

    if (n > 1) {
        int m = n / 2;
        if (trySpawnThread()) {
            ThreadData * data = new ThreadData{ &arr, lo, n};
            ThreadCreate(&handle, sortPart, data);
            ThreadJoin(handle);
        } else {
            oddEvenMergeSort(arr, lo, m);
            oddEvenMergeSort(arr, lo + m, m);
        }
        oddEvenMerge(arr, lo, n, 1);
    }
}



void* sortPart(void* arg) {
    ThreadData* data = (ThreadData*)arg; 
    std::cout << "Thread started. Active threads: " << activeThreads << "\n";
    oddEvenMergeSort(*data->arr, data->lo, data->n); 
    std::cout << "Thread finished. Active threads: " << activeThreads << "\n";
    threadFinished(); 
    delete data;

    return nullptr;
}