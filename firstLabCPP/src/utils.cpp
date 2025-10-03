#include "../include/utils.h"

std::string reverseString(const std::string& s) {
    std::string rev;
    
    // Просто идем с конца строки и добавляем символы в новую строку
    for (int i = s.size() - 1; i >= 0; i--) {
        rev += s[i];
    }
    
    return rev;
}