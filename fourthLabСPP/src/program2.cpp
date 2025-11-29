#include <iostream>
#include <dlfcn.h>
#include <string>


// указатели на функции
int (*GCF_func)(int, int) = nullptr;
float (*Square_func)(float, float) = nullptr;


void* handle = nullptr;


void loadLib(const char* path) {
if (handle) dlclose(handle);
handle = dlopen(path, RTLD_LAZY);


if (!handle) {
std::cerr << "dlopen error: " << dlerror() << std::endl;
exit(1);
}


GCF_func = (int (*)(int,int)) dlsym(handle, "GCF");
Square_func = (float (*)(float,float)) dlsym(handle, "Square");
}


int main() {
std::cout << "Program 2 (runtime dynamic loading)" << std::endl;


// стартуем с первой либы
loadLib("./libimpl1.dylib");


while (true) {
int cmd;
std::cin >> cmd;
if (!std::cin) break;


if (cmd == 0) {
// переключаем
static bool toggle = false;
toggle = !toggle;
loadLib(toggle ? "./libimpl2.dylib" : "./libimpl1.dylib");
std::cout << "Library switched" << std::endl;
}
else if (cmd == 1) {
int a, b;
std::cin >> a >> b;
std::cout << GCF_func(a, b) << std::endl;
}
else if (cmd == 2) {
float a, b;
std::cin >> a >> b;
std::cout << Square_func(a, b) << std::endl;
}
}


if (handle) dlclose(handle);
}