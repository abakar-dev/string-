#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;

  while (*str1 != '\0' && result == S21_NULL) {
    const char *p = str2;
    while (*p != '\0') {
      if (*str1 == *p) {
        result = (char *)str1;
        break;
      }
      p++;
    }
    str1++;
  }
  return result;
}

// int main() {
//     const char *str1 = "Hello, World!";
//     const char *str2 = "a, W";
//     char *result = s21_strpbrk(str1, str2);

//     if (result) {
//         printf("Первый соответствующий символ: %c\n", *result);
//     } else {
//         printf("Соответствующий символ не найден\n");
//     }
//     return 0;
// }