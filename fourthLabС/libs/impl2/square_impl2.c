#include "square.h"

// Реализация 2: Площадь прямоугольного треугольника
// S = (A * B) / 2, где A и B - катеты
float Square(float A, float B) {
    if (A <= 0 || B <= 0) {
        return -1.0f; // Ошибка: стороны должны быть положительными
    }
    
    return (A * B) / 2.0f;
}
