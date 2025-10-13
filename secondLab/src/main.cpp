#include <iostream>
#include <vector>
#include "../include/batcher_sort.h"
#include <chrono> //чтоб время измерять
#include <cstdlib> //чтоб рандом было
#include <ctime>  //чтоб для рандома тоже


int main(int argc, char* argv[]) {
    int maxThreads;
    if (argc > 1) {
        maxThreads = std::atoi(argv[1]);
        if (maxThreads > 16) maxThreads = 16; 
    }
    std::srand(std::time(nullptr));

    const int N = 256;
    std::vector<int> arr(N);

    for (int i = 0; i < N; i++) {
        arr[i] = std::rand() % 1000;
    }

    std::cout << "Before sorting:\n";
      for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    OddEvenSorter sorter(arr, maxThreads);
    sorter.start();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "After sorting:\n";
    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    std::cout << "Time: " 
          << std::chrono::duration<double>(end-start).count() 
          << " seconds\n";
    return 0;
}