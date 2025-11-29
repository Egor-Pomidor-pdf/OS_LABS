#include <stdio.h>
#include <stdlib.h>
#include "gcf.h"
#include "square.h"

int main() {
    printf("=== Программа №1: Статическая линковка ===\n");
    printf("Использует библиотеку, выбранную при компиляции\n");
    printf("Команды: 1 <a> <b> - вызов GCF, 2 <a> <b> - вызов Square, 0 - выход\n\n");
    
    int cmd;
    while (1) {
        printf("> ");
        if (scanf("%d", &cmd) != 1) {
            break;
        }
        
        if (cmd == 0) {
            printf("Выход из программы\n");
            break;
        } else if (cmd == 1) {
            int a, b;
            if (scanf("%d %d", &a, &b) != 2) {
                printf("Ошибка ввода\n");
                continue;
            }
            
            int result = GCF(a, b);
            if (result < 0) {
                printf("Ошибка: числа должны быть натуральными\n");
            } else {
                printf("GCF(%d, %d) = %d\n", a, b, result);
            }
        } else if (cmd == 2) {
            float a, b;
            if (scanf("%f %f", &a, &b) != 2) {
                printf("Ошибка ввода\n");
                continue;
            }
            
            float result = Square(a, b);
            if (result < 0) {
                printf("Ошибка: стороны должны быть положительными\n");
            } else {
                printf("Square(%.2f, %.2f) = %.2f\n", a, b, result);
            }
        } else {
            printf("Неизвестная команда\n");
        }
    }
    
    return 0;
}
