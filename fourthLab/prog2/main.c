#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

// Указатели на функции из динамической библиотеки
int (*GCF_ptr)(int, int) = NULL;
float (*Square_ptr)(float, float) = NULL;

// Дескриптор текущей библиотеки
void *lib_handle = NULL;

// Загрузка библиотеки по номеру реализации
int load_library(int impl_num) {
    // Закрываем текущую библиотеку, если была загружена
    if (lib_handle != NULL) {
        dlclose(lib_handle);
        lib_handle = NULL;
        GCF_ptr = NULL;
        Square_ptr = NULL;
    }
    
    // Формируем имя библиотеки
    char lib_name[256];
    snprintf(lib_name, sizeof(lib_name), "./libimpl%d.dylib", impl_num);
    
    // Открываем библиотеку
    lib_handle = dlopen(lib_name, RTLD_LAZY);
    if (!lib_handle) {
        fprintf(stderr, "Ошибка загрузки библиотеки %s: %s\n", lib_name, dlerror());
        return -1;
    }
    
    // Получаем адрес функции GCF
    GCF_ptr = (int (*)(int, int))dlsym(lib_handle, "GCF");
    char *error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска функции GCF: %s\n", error);
        dlclose(lib_handle);
        lib_handle = NULL;
        return -1;
    }
    
    // Получаем адрес функции Square
    Square_ptr = (float (*)(float, float))dlsym(lib_handle, "Square");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "Ошибка поиска функции Square: %s\n", error);
        dlclose(lib_handle);
        lib_handle = NULL;
        GCF_ptr = NULL;
        return -1;
    }
    
    printf("Успешно загружена библиотека: %s\n", lib_name);
    return 0;
}

int main() {
    printf("=== Программа №2: Динамическая загрузка библиотек ===\n");
    printf("Команды:\n");
    printf("  0 <номер> - переключить реализацию (1 или 2)\n");
    printf("  1 <a> <b> - вызов GCF\n");
    printf("  2 <a> <b> - вызов Square\n");
    printf("  exit - выход\n\n");
    
    // По умолчанию загружаем первую реализацию
    if (load_library(1) != 0) {
        fprintf(stderr, "Не удалось загрузить библиотеку по умолчанию\n");
        return 1;
    }
    
    char input[256];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Проверка на команду выхода
        if (strncmp(input, "exit", 4) == 0) {
            printf("Выход из программы\n");
            break;
        }
        
        int cmd;
        if (sscanf(input, "%d", &cmd) != 1) {
            printf("Неверный формат команды\n");
            continue;
        }
        
        if (cmd == 0) {
            // Переключение библиотеки
            int impl_num;
            if (sscanf(input, "%d %d", &cmd, &impl_num) != 2) {
                printf("Формат: 0 <номер_реализации>\n");
                continue;
            }
            
            if (impl_num != 1 && impl_num != 2) {
                printf("Доступны только реализации 1 и 2\n");
                continue;
            }
            
            if (load_library(impl_num) != 0) {
                fprintf(stderr, "Не удалось переключить библиотеку\n");
            }
        } else if (cmd == 1) {
            // Вызов GCF
            if (GCF_ptr == NULL) {
                printf("Библиотека не загружена\n");
                continue;
            }
            
            int a, b;
            if (sscanf(input, "%d %d %d", &cmd, &a, &b) != 3) {
                printf("Формат: 1 <a> <b>\n");
                continue;
            }
            
            int result = GCF_ptr(a, b);
            if (result < 0) {
                printf("Ошибка: числа должны быть натуральными\n");
            } else {
                printf("GCF(%d, %d) = %d\n", a, b, result);
            }
        } else if (cmd == 2) {
            // Вызов Square
            if (Square_ptr == NULL) {
                printf("Библиотека не загружена\n");
                continue;
            }
            
            float a, b;
            if (sscanf(input, "%d %f %f", &cmd, &a, &b) != 3) {
                printf("Формат: 2 <a> <b>\n");
                continue;
            }
            
            float result = Square_ptr(a, b);
            if (result < 0) {
                printf("Ошибка: стороны должны быть положительными\n");
            } else {
                printf("Square(%.2f, %.2f) = %.2f\n", a, b, result);
            }
        } else {
            printf("Неизвестная команда\n");
        }
    }
    
    // Закрываем библиотеку перед выходом
    if (lib_handle != NULL) {
        dlclose(lib_handle);
    }
    
    return 0;
}
