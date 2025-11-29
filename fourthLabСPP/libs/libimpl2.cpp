#include "contract.h"
#include <cmath>


extern "C" int GCF(int A, int B) {
int g = 1;
int m = std::fmin(A, B);
for (int i = 1; i <= m; i++) {
if (A % i == 0 && B % i == 0) g = i;
}
return g;
}


extern "C" float Square(float A, float B) {
return (A * B) / 2.0f;
}