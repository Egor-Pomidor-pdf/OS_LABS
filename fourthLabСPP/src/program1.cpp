#include <iostream>
#include "contract.h"


int main() {
std::cout << "Program 1 (compile-time linking)" << std::endl;
while (true) {
int cmd;
std::cin >> cmd;
if (!std::cin) break;


if (cmd == 1) {
int a, b;
std::cin >> a >> b;
std::cout << GCF(a, b) << std::endl;
}
else if (cmd == 2) {
float a, b;
std::cin >> a >> b;
std::cout << Square(a, b) << std::endl;
}
}
}

