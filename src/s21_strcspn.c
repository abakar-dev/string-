#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i, j;
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t len2 = s21_strlen(str2);
  s21_size_t result = len1;

  for (i = 0; i < len1; i++) {
    for (j = 0; j < len2; j++) {
      if (str1[i] == str2[j]) {
        result = i;
        break;
      }
    }
    if (result != len1) {
      break;
    }
  }
  return result;
}

// int main() {

//     const char *str1 = "Hello, World!";
//     const char *str2 = "ynvW";
//     s21_size_t result = s21_strcspn(str1, str2);
//     printf("Длина начального сегмента: %zu\n", result);
//     return 0;
// }