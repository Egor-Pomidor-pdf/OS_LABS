#include "contract.h"
#include <cmath>


extern "C" int GCF(int A, int B) {
while (B != 0) {
int t = B;
B = A % B;
A = t;
}
return A;
}


extern "C" float Square(float A, float B) {
return A * B;
}