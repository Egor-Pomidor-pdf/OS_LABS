#include "square.h"

// Реализация 1: Площадь прямоугольника
// S = A * B
float Square(float A, float B) {
    if (A <= 0 || B <= 0) {
        return -1.0f; // Ошибка: стороны должны быть положительными
    }
    
    return A * B;
}
