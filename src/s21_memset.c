#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  /* cppcheck-suppress cstyleCast */
  unsigned char *s = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    s[i] = c + '\0';
  }
  return s;
}

// int main() {
//     unsigned char src[10];

//     s21_memset (src, '0', 8);

//     printf("%s \n", src);

//     return 0;
// }