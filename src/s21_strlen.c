#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

// int main() {
//     const char *str = "Hello, World!";
//     size_t length = s21_strlen(str);
//     printf("Длина строки: %zu\n", length);
//     return 0;
// }