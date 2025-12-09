#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_start = dest;
  s21_size_t dest_i = s21_strlen(dest);
  s21_size_t src_i = 0;

  while (n > 0 && src[src_i] != '\0') {
    dest_start[dest_i] = src[src_i];
    n--;
    dest_i++;
    src_i++;
  }

  dest[dest_i] = '\0';

  return dest_start;
}

// int main() {
//     char dest[25] = "sfsrfgs";
//     char src[] = "World";
//     s21_strncat(dest, src, 5); // добавляет 3 символа из src в dest
//     printf("%s\n", dest);  // Результат: HelloWor
//     return 0;
// }